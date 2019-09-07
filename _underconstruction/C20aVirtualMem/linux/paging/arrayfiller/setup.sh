#!/bin/bash

uid=`id -u`
if [ ${uid} -ne 0 ]; then
    echo ">> This script needs to run as root."
    exit 1
fi


if [ $# -lt 1 ]; then 
   numofpages=64
else
   numofpages=$1
fi

pagesize=`getconf PAGESIZE`
memlimit=$((${numofpages} * ${pagesize}))


if [ -r /sys/fs/cgroup/memory/cisc3320arrayfilldemo ]; then
    cgdelete -g memory:/cisc3320arrayfilldemo
fi
cgcreate -g memory:/cisc3320arrayfilldemo
echo ${memlimit} > /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.limit_in_bytes

echo ">> In /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.limit_in_bytes:"
cat /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.limit_in_bytes
echo ">> Physical memory limit set as ${memlimit} bytes or ${numofpages} pages."

if [ $# -lt 2 ] ; then
    echo ">> To run an array-filler program, issue the following as root:"
    echo -e "\tcgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbycolumn"
    echo -e "\t\tor"
    echo -e "\tcgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbyrow"
    exit 0
fi
program=$2
echo ">> Running ${program}"
cgexec -g memory:cisc3320arrayfilldemo ./${program}
