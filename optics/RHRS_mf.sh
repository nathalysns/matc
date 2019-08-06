#!/bin/bash

echo Spring 2018 Runs \( 1 \) or Fall 2018  Runs \( 2 \)
read set

if [ "$set" = "1" ]; then
        RHRS=(93080 93069 93086 93082 93113)
else
        RHRS=(93486 93487 93490 93491 93492 93498 93499 93500 93510 93511 93512 93513 93514 93515 93516 93517 93518 93519 93538 93539 93543 93544 93576 93582 93584 93585 93644 93663 93664 93665 93749 93821)
fi

for run in ${RHRS[@]}
do 
  analyzer -l -b -q \" multifoils_check.C\($run\) \"
  echo $run
done 
