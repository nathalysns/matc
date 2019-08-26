#!/bin/bash

input="../runs_list.csv"
while IFS= read -r line
do
  #echo "$line"
	while IFS=',' read -ra var; do
	if [ "${var[1]}" == "Single Carbon" ]
		then
		echo ${var[0]} 
    		analyzer -l -b -q Ccheck.C"(${var[0]})"
	fi
    done <<< "$line"
done < "$input"
