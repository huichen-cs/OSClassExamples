#!/bin/sh

# apt-get install cgroup-tools

cgcreate -g memory:/cisc3320arrayfilldemo
echo $(( 64 * 4 * 1024 )) > /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.limit_in_bytes
echo $(( 128 * 1024 * 1024 )) > /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.memsw.limit_in_bytes

#cgexec -g memory:cisc3320arrayfilldemo arrayfillerbycolumn
