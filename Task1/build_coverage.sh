#!/bin/bash

gcc -c -std=c99 --coverage -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion ./*.c -lm
gcc --coverage -o app.exe ./*.o -lm
