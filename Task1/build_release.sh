#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion ./*.c -lm
gcc -o app.exe ./*.o -lm
