#!/bin/bash

gcc -std=c99 -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g ./*.c -lm
gcc -o app.exe ./*.o
