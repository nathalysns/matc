#!/bin/bash

echo Spring 2018 Runs \( 1 \) or Fall 2018  Runs \( 2 \)
read set
echo $set

if [ "$set" = "1" ]; then 
   RHRS=(93047 93063 93082 93099 93122 93137)
else
   RHRS=(93588 93589 93626 93642 93688 93938 94014 94069 94082 94090 94091)
fi

for run in ${RHRS[@]}
do 
  #analyzer -l -b -q \" optics_check.C\($run\) \"
  echo $run
done 
