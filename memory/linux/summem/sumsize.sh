#!/bin/bash

pagesize=`getconf PAGE_SIZE`
filelist=`ls /proc`

sumsize=0
sumrss=0
for f in ${filelist[*]}; do
    echo $f | grep -q "^[0-9]\+$"
    if [ $? -eq 0 ]; then
        filename=/proc/$f/stat
        filecontent=`cat ${filename}`
        if [ $? -ne 0 ]; then
            echo "Process (pid=${f}) has terminated"
        else
            sizebytes=`echo ${filecontent} | cut -d' '  -f23 ${filename}`
            rsspages=`echo ${filecontent} | cut -d' ' -f24 ${filename}`
            rssbytes=`expr ${rsspages} "*" ${pagesize}`
            sumsize=`expr ${sumsize} + ${sizebytes}`
            sumrss=`expr ${sumrss} + ${rssbytes}`
            echo ${filename} $sizebytes $rsspages
        fi 
    fi
done

sumsizekb=`expr ${sumsize} / 1024`
sumrsskb=`expr ${sumrss} / 1024`
echo "Total size is ${sumsizekb} kB"
echo "Total rss is ${sumrsskb} kB"
