#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Usage: $0 PID"
	exit 1
fi

pid=$1
while true; do
	if [ ! -r "/proc/${pid}/stat" ]; then
		echo "Process ${pid} terminated."
		exit 0
	fi
	if ! filecontent=$(cat "/proc/${pid}/stat"); then
		echo "Process (pid=${pid}) not found in the system"
		exit 1
	fi
	minorfaults=$(echo "${filecontent}" | cut -d' ' -f10)
	majorfaults=$(echo "${filecontent}" | cut -d' ' -f12)

	echo "Page Faults by Process (pid=${pid}): Minor ${minorfaults} Major ${majorfaults}"
	sleep 5
done
