#!/bin/bash

pprog=('-' '\' '|' '/' '-' '\' '|')
nruns=10000
i=1
while [ ${i} -lt ${nruns} ]; do
    result=`java ProducerConsumer | grep "The sum" | \
        sed -rn 's/^The sum is ([0-9]+).*$/\1/p'`
    let j=${i}%7
    echo -n -e "\rThe result is ${result} ${pprog[${j}]} at run ${i}"
    if [ x"${result}" != x"49995000" ]; then
        echo -e \
            " \nIs the result ${result} wrong? (or the output intermingled?)"
        echo -e \
            "\tThe line is\n\t${resultline}"
    fi
    let i=${i}+1
done
echo -e "\nCompleted!"
