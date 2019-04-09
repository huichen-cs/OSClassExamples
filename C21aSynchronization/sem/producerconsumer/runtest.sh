#!/bin/bash

pprog=('-' '\' '|' '/' '-' '\' '|')
nruns=10000
i=1
while [ ${i} -lt ${nruns} ]; do
    result=`./producerconsumer | \
        grep "The sum" | \
        sed -rn 's/^The sum is ([0-9]+).*$/\1/p'`
    let j=${i}%8
    echo -n -e "\rThe result is ${result} ${pprog[${j}]} at run ${i}"
    if [ ${result} -ne 49995000 ]; then
        echo "The result ${result} is wrong!"
        exit 1
    fi
    let i=${i}+1
done
echo "NO error detected"
