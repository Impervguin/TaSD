#!/bin/bash

cp ./func_tests/scripts/bin_text.c ./bin_text.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c ./bin_text.c -o ./func_tests/scripts/bin_text.o -lm
rm ./bin_text.c
gcc -o ./func_tests/scripts/b2t.exe ./func_tests/scripts/bin_text.o -lm