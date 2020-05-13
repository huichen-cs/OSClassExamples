#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 PID"
    exit 1
fi

pid=$1
while [ 1 ]; do
		if [ ! -r /proc/${pid}/stat ]; then
			echo "Process ${pid} terminated."
			exit 0
		fi
		filecontent=$(cat /proc/${pid}/stat)
		if [ $? -ne 0 ]; then
			echo "Process (pid=${pid}) not found in the system"
			exit 1
		fi
		minorfaults=$(echo ${filecontent} | cut -d' ' -f10)
		majorfaults=$(echo ${filecontent} | cut -d' ' -f12)

		echo "Page Faults by Process (pid=${pid}): Minor ${minorfaults} Major ${majorfaults}"
		sleep 5
done


