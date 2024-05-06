#!/bin/bash

cgname=$(mount | grep -E "[[:space:]]/sys/fs/cgroup[[:space:]]" | cut -d' ' -f1)
if [ "${cgname}" != "cgroup" ]; then
    echo "expected cgroup is mounted on /sys/fs/cgroup, but not found"
    exit 1
fi

uid=`id -u`
if [ ${uid} -ne 0 ]; then
    echo ">> This script needs to run as root."
    exit 1
fi

which cgexec > /dev/null 2>&1
if [ $? -ne 0 ]; then
	echo -n ">> Installing the cgroup-tools package ..."
	apt-get install -y cgroup-tools iotop > /dev/null 2>&1
	if [ $?  -ne 0 ]; then 
		echo " Failed and quitting ..."
		exit 1
	else
		echo " Succeeded."
	fi
fi

if [ $# -lt 1 ]; then 
   numofpages=65
else
   numofpages=$1
fi

pagesize=`getconf PAGESIZE`
memlimit=$((${numofpages} * ${pagesize}))


if [ -r /sys/fs/cgroup/memory/osarrayfilldemo ]; then
    cgdelete -g memory:/osarrayfilldemo
fi
cgcreate -g memory:/osarrayfilldemo
if [ $? -ne 0 ]; then
	echo "Failed to create the cgroup for arrayfilleri. Qutitting ..."
	exit 1
fi
echo ${memlimit} > /sys/fs/cgroup/memory/osarrayfilldemo/memory.limit_in_bytes

echo ">> In /sys/fs/cgroup/memory/osarrayfilldemo/memory.limit_in_bytes:"
cat /sys/fs/cgroup/memory/osarrayfilldemo/memory.limit_in_bytes
echo ">> Physical memory limit set as ${memlimit} bytes or ${numofpages} pages."

make > /dev/null 2>&1 

if [ $# -lt 2 ] ; then
    echo ">> To run an array-filler program, issue the following as root:"
    echo -e "\tcgexec -g memory:osarrayfilldemo ./arrayfillerbycolumn"
    echo -e "\t\tor"
    echo -e "\tcgexec -g memory:osarrayfilldemo ./arrayfillerbyrow"
    exit 0
fi
program=$2
echo ">> Running ${program}"
cgexec -g memory:osarrayfilldemo ./${program}
