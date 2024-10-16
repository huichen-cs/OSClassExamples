#!/bin/bash

euid=$(id -u)
if [ "${euid}" -ne 0 ]; then
	echo "You must run this script as root (e.g., via su or sudo)"
	exit 1
fi

numhugepages=100
if [ $# -ge 1 ]; then
	numhugepages=$1
fi

freemem=$(grep MemFree /proc/meminfo | grep -o "[0-9]\+")
hugepagesize=$(grep Hugepagesize /proc/meminfo | grep -o "[0-9]\+")
maxnumofhugepages=$((freemem / hugepagesize))
echo "You system's hugepage size is ${hugepagesize} KB."
echo "Your available memory is ${freemem} KB."
echo "You can have at most ${maxnumofhugepages} huge pages."

threshold=0.6
isok=$(echo "${numhugepages} >= ${threshold}*${maxnumofhugepages}" | bc -l)
if [ "${isok}" -eq 1 ]; then
	echo "You requested ${numhugepages} huge pages, exceeding free memory by the factor of ${threshold}"
	echo "Rerun the command with a command line argument"
	echo "Usage: $0 NUM_HUGE_PAGES"
	exit 1
fi
echo "You requested ${numhugepages} huge pages"

if ! sysctl -w vm.nr_hugepages="${numhugepages}"; then
	echo "Failed to allocate huge pages via sysctl"
	exit 1
fi
echo "The huge page allocation are as follows:"
grep -i "Hugepage" /proc/meminfo

apt-get install -y x86info cpuid libhugetlbfs0 >/dev/null 2>&1

make

if [ -r /usr/lib/i386-linux-gnu/libhugetlbfs-2.20.so ]; then
	LIBHUGETLBFS=/usr/lib/i386-linux-gnu/libhugetlbfs-2.20.so
elif [ -r /usr/lib/libhugetlbfs.so ]; then
	LIBHUGETLBFS=/usr/lib/libhugetlbfs.so
else
	echo "Have you installed libhugetlbfs?"
	exit 1
fi
echo "time LD_PRELOAD=${LIBHUGETLBFS} \
  HUGETLB_MORECORE=yes ./worker ${hugepagesize} 4"
time LD_PRELOAD=${LIBHUGETLBFS} \
	HUGETLB_MORECORE=yes ./worker "${hugepagesize}" 4

echo "time ./worker ${hugepagesize} 4"
time ./worker "${hugepagesize}" 4
