#!/bin/bash


nprocesses=4
if [ $# -gt 0 ]; then
    nprocesses=$1
fi

i=0
nruns=10000
error=0
while [ ${i} -lt ${nruns} ]; do
    ntids=` ./nextpiddemo | grep "local tid" | sed -e 's/^local tid: //' | \
        sort | uniq | wc -l`
    echo ${ntids}
    let i=${i}+1
done 

