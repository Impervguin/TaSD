#!/bin/bash

clang -std=c99 -fsanitize=memory -fPIE -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fno-omit-frame-pointer -O0 -g ./*.c
clang -fsanitize=memory -fPIE -o app.exe  ./*.o
