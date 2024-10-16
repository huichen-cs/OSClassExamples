#!/bin/bash

pagesize=$(getconf PAGE_SIZE)

sumsize=0
sumrss=0
for f in /proc/*; do
	if echo "$f" | grep -q "^[0-9]\+$"; then
		filename=/proc/$f/stat
		if ! filecontent=$(cat "${filename}"); then
			echo "Process (pid=${f}) has terminated"
		else
			sizebytes=$(echo "${filecontent}" | cut -d' ' -f23)
			rsspages=$(echo "${filecontent}" | cut -d' ' -f24)
			rssbytes=$((rsspages * pagesize))
			sumsize=$((sumsize + sizebytes))
			sumrss=$((sumrss + rssbytes))
			echo "${filename} $sizebytes $rsspages"
		fi
	fi
done

sumsizekb=$((sumsize / 1024))
sumrsskb=$((sumrss / 1024))
echo "Total size is ${sumsizekb} kB"
echo "Total rss is ${sumrsskb} kB"
