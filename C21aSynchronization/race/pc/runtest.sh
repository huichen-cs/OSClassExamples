#!/bin/bash

nruns=10000
i=1
while [ ${i} -lt ${nruns} ]; do
    result=`./producerconsumer | grep "The sum" | sed -e 's/^The sum is '//g`
    echo -n -e "\rThe result is ${result}"
    if [ ${result} -ne 49995000 ]; then
        echo -e "\nThe result ${result} is wrong!"
        exit 1
    fi
    let i=${i}+1
done
echo -e "\nNO error detected"
