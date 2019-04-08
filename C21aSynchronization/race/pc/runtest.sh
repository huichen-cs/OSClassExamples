#!/bin/bash

nruns=100
i=1
while [ ${i} -lt ${nruns} ]; do
    ./producerconsumer | grep "The sum" | sed -e 's/^The sum is '//g
    let i=${i}+1
done
