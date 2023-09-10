#!/bin/bash

SUCCESS="\033[92m"
ERROR="\033[91m"
RESET="\033[0m"
KEYS=""
bash clean.sh
bash build_release.sh
# shellcheck disable=SC2086
bash ./func_tests/scripts/func_tests.sh -v $KEYS # Если добавить в кавычки, то вся строка keys будет параметром

out=$(mktemp)

bash clean.sh
bash build_debug_asan.sh
# shellcheck disable=SC2086
bash ./func_tests/scripts/func_tests.sh $KEYS 2> "$out"

if [[ -s "$out" ]]; then
  echo -e Address sanitizer: "$ERROR"failed"$RESET"
  cat "$out"
else
  echo -e Address sanitizer: "$SUCCESS"passed"$RESET"
fi

bash clean.sh
bash build_debug_msan.sh

# shellcheck disable=SC2086
bash ./func_tests/scripts/func_tests.sh $KEYS 2> "$out"

if [[ -s "$out" ]]; then
  echo -e Memory sanitizer: "$ERROR"failed"$RESET"
  cat "$out"
else
  echo -e Memory sanitizer: "$SUCCESS"passed"$RESET"
fi

bash clean.sh
bash build_debug_ubsan.sh
# shellcheck disable=SC2086
bash ./func_tests/scripts/func_tests.sh $KEYS 2> "$out"

if [[ -s "$out" ]]; then
  echo -e Undefined behavior sanitizer: "$ERROR"failed"$RESET"
  cat "$out"
else
  echo -e Undefined behavior sanitizer: "$SUCCESS"passed"$RESET"
fi

bash clean.sh
bash collect_coverage.sh "$KEYS"