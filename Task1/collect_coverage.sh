#!/bin/bash

./clean.sh

bash build_coverage.sh
# shellcheck disable=SC2086
bash func_tests/scripts/func_tests.sh $1
gcov main.c

