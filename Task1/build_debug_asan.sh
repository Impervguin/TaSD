#!/bin/bash

clang -c -std=c99 -fsanitize=address -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fno-omit-frame-pointer -O0 -g ./*.c
clang -fsanitize=address -o app.exe  ./*.o
