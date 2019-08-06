#!/bin/bash


#LHRS=(891 893 894 895 896 897 898 899 901 941)
LHRS=(822 842 843 844 846 848 849 850 851 853 854 855 856 948)
for run in ${LHRS[@]}
do 
  analyzer -l -b -q \" multifoils_check.C\($run\) \"
  echo $run
done 
