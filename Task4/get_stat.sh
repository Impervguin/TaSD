#!/bin/bash

SIZES="500 1000 2000 5000 7500 10000"

make statistics.exe

for size in $SIZES
do
  echo -e "\033[93m"Size:"\033[0m" $size
  echo
  ./statistics.exe ./data/operation/data_"$size".txt
  echo
done