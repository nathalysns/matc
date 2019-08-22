#!/bin/bash

input="../runs_list.csv"
while IFS= read -r line
do
  #echo "$line"
	while IFS=',' read -ra var; do
    	analyzer -l -b -q raster_check.C"(${var[0]}, \"${var[1]}\")"
    done <<< "$line"
done < "$input"