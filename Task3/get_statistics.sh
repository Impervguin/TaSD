#!/bin/bash

SIZES="10"
PROCS="10 20 40 80"

make statistics.exe

for size in $SIZES
do
  for proc in $PROCS
  do
    echo -e "\033[93m"Size:"\033[0m" $size "\033[93m"Proc:"\033[0m" $proc
    echo
    ./statistics.exe ./data/mat/mat_"$size"_"$proc".txt ./data/vec/vec_"$size"_"$proc".txt
    echo
  done
done
