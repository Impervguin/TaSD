#!/bin/bash
# Для каждого sh файла запускаем shellcheck
for file in *.sh func_tests/scripts/*.sh
do
    echo Checking "$file"...
    shellcheck "$file"
done

