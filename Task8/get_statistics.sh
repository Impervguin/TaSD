#!/bin/bash

SIZES="5 10 15 20 25 30"
PROCS="5 10 15 20 30 50"

make statistics.exe

for size in $SIZES
do
  for proc in $PROCS
  do
    echo -e "\033[93m"Size:"\033[0m" $size "\033[93m"Proc:"\033[0m" $proc
    echo
    ./statistics.exe ./data/graph_"$size"_"$proc".txt
    echo
  done
done
