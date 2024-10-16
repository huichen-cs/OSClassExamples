#!/bin/bash

nruns=10000
i=1
while [ ${i} -lt ${nruns} ]; do
	resultline=$(./producerconsumer |
		grep "The sum")
	result=$(echo "${resultline}" |
		sed -rn 's/^The sum is ([0-9]+).*$/\1/p')
	echo -n -e "\rThe result is ${result} at run ${i}"
	if [ x"${result}" != x"49995000" ]; then
		echo -e \
			" \nIs the result ${result} wrong? (or the output intermingled?)"
		echo -e \
			"\tThe line is\n\t${resultline}"
	fi
	i=$((i + 1))
done
echo -e "\nCompleted!\n\n"
