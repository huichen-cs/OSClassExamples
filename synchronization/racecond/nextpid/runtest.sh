#!/bin/bash

nprocesses=4
if [ $# -gt 0 ]; then
	nprocesses=$1
fi

i=0
nruns=10000
while [ ${i} -lt ${nruns} ]; do
	ntids=$(./nextpiddemo "${nprocesses}" |
		grep "local tid" | sed -e 's/^local tid: //' |
		sort | uniq | wc -l)
	echo "ntids = ${ntids}"
	i=$((i + 1))
done
