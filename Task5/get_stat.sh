#!/bin/bash

SIZES="1000 2000 3000 5000 10000 20000"

make statistics.exe

for size in $SIZES
do
  echo -e "\033[93m"Size:"\033[0m" $size
  echo
  ./statistics.exe "$size"
  echo
done