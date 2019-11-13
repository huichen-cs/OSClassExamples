#!/bin/bash

euid=`id -u`
if [ ${euid} -ne 0 ]; then
    echo "You must run this script as root (e.g., via su or sudo)"
    exit 1
fi

numhugepages=100
if [ $# -ge 1 ]; then
   numhugepages=$1
fi


freemem=`grep MemFree /proc/meminfo | grep -o "[0-9]\+"`
hugepagesize=`grep Hugepagesize /proc/meminfo | grep -o "[0-9]\+"`
maxnumofhugepages=`expr ${freemem} / ${hugepagesize}`
echo "You system's hugepage size is ${hugepagesize} KB."
echo "Your available memory is ${freemem} KB."
echo "You can have at most ${maxnumofhugepages} huge pages."

threshold=0.6
isok=`echo "${numhugepages} >= ${threshold}*${maxnumofhugepages}" | bc -l`
if [ ${isok} -eq 1 ]; then 
    echo "You requested ${numhugepages} huge pages, exceeding ${threshold} of free memory"
    exit 1
fi
echo "You requested ${numhugepages} huge pages"

sysctl -w vm.nr_hugepages=${numhugepages}
if [ $? -ne 0 ]; then
    echo "Failed to allocate huge pages via sysctl"
    exit 1
fi
echo "The huge page allocation are as follows:"
grep -i "Hugepage" /proc/meminfo

