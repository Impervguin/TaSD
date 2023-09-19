#!/bin/bash

OK=0 # Только для данных, без проверки памяти - успех

MEMORY_OUTPUT=0   # Память - успех, данные - успех
NMEMORY_OUTPUT=2  # Память - провал, данные - успех
NMEMORY_NOUTPUT=3 # Память - успех, данные - провал
MEMORY_NOUTPUT=4  # Память - провал, данные - провал


# Путь к тестам и скриптам из папки проекта
PATH_TO_DATA="./func_tests/data"
PATH_TO_SCRIPTS="./func_tests/scripts/"

# Счетчики различных проваленных и общега числа тестов
fpt_num=0 # Число проваленных позитивных тестов
pt_num=0  # Общее число позитивных тестов
fnt_num=0 # Число проваленных негативных тестов
nt_num=0  # Общее количество негативных тестов

# Коды цветов для различной информации
SUCCESS="\033[92m"
ERROR="\033[91m"
INFO2="\033[93m"
RESET="\033[0m"
function test_output {
  if [[ $rc -eq $OK ]]; then
    echo -e Test: "$SUCCESS"passed"$RESET"
  else
    echo -e Test: "$ERROR"failed"$RESET"
    echo -e Input: "$INFO2""$(cat "$input")""$RESET"
    echo -e Expected output: "$INFO2""$(cat "$expected")""$RESET"
    echo -e Output: "$INFO2""$(cat "$out")""$RESET"
  fi
}

function test_memory_output {
  if [[ $rc -eq $MEMORY_OUTPUT ]]; then
    local test_passed=1
    local mem_passed=1
  elif [[ $rc -eq $NMEMORY_OUTPUT ]]; then
    local test_passed=1
    local mem_passed=0
  elif [[ $rc -eq $NMEMORY_NOUTPUT ]]; then
    local test_passed=0
    local mem_passed=0
  elif [[ $rc -eq $MEMORY_NOUTPUT ]]; then
    local test_passed=0
    local mem_passed=1
  fi
  if [[ $mem_passed -eq 1 ]]; then
    echo -e Memory: "$SUCCESS"passed"$RESET"
  else
    echo -e Memory: "$ERROR"failed"$RESET"
  fi
  if [[ $test_passed -eq 1 ]]; then
    echo -e Test: "$SUCCESS"passed"$RESET"
  else
    echo -e Test: "$ERROR"failed"$RESET"
    echo -e Input: "$INFO2""$(cat "$input")""$RESET"
    echo -e Expected output: "$INFO2""$(cat "$expected")""$RESET"
    echo -e Output: "$INFO2""$(cat "$out")""$RESET"
  fi
}

# Ввод ключей
for param in "$@"; do
  if [[ $param == "-v" ]] || [[ $param == "--verbose" ]]; then # Ключ вывода работы программы
    verbose=1
  elif [[ $param == "--mem-check" ]]; then # Ключ проверки памяти с valgrind
    memory=1
    key_mem="--mem-check"
  fi
  shift
done

out=$(mktemp)
# Позитивное тестирование
for input in "$PATH_TO_DATA"/pos_[0-9][0-9]_in.txt; do # Проходимся по всем входным тестам

  if [[ "$input" == "$PATH_TO_DATA/pos_[0-9][0-9]_in.txt" ]]; then
    echo -e "$INFO2""No positive tests found""$RESET"
    break
  fi

  test_num=$(echo "$input" | grep -o "[0-9][0-9]") # Номер позитивного теста

  expected=$PATH_TO_DATA/pos_"$test_num"_out.txt # Файл с эталонным выводом

  if [[ -f $expected ]]; then # Проверка на существование файла с ожидаемым выводом
    # Информация о тесте выводится самим скриптом
    bash "$PATH_TO_SCRIPTS"pos_case.sh "$input" "$expected" "$key_mem" --out="$out"
    rc=$?
    # Если код возврата не соответствует OK, тест не прошел по памяти или по данным
    if [[ $rc -ne $OK ]]; then
      fpt_num=$((fpt_num + 1))
    fi
    if [[ $verbose -eq 1 ]]; then
      echo -e "\n------------------------------\n"
      echo -e "$INFO2"Positive"$RESET" test "$INFO2""$test_num""$RESET"
      if [[ $memory -eq 1 ]]; then
        test_memory_output
      else
        test_output
      fi
    fi
  else
    if [[ $verbose -eq 1 ]]; then
      echo Cannot find "$expected" file. # Не найлен файл с эталонным выводом
    fi
  fi
  pt_num=$((pt_num + 1))
done

# Негативное тестирование
for input in "$PATH_TO_DATA"/neg_[0-9][0-9]_in.txt; do

  if [[ "$input" == "$PATH_TO_DATA/neg_[0-9][0-9]_in.txt" ]]; then
    echo -e "$INFO2""No negative tests found""$RESET"
    break
  fi

  test_num=$(echo "$input" | grep -o "[0-9][0-9]")

  expected=$PATH_TO_DATA/neg_"$test_num"_out.txt # Файл с эталонным выводом

  if [[ -f $expected ]]; then # Проверка на существование файла с ожидаемым выводом
    # Информация о тесте выводится самим скриптом
    bash "$PATH_TO_SCRIPTS"neg_case.sh "$input" "$expected" "$key_mem" --out="$out"
    rc=$?
    # Если код возврата не соответствует OK, тест не прошел по памяти или по данным
    if [[ $rc -ne $OK ]]; then
      fnt_num=$((fnt_num + 1))
    fi
    if [[ $verbose -eq 1 ]]; then
      echo -e "\n------------------------------\n"
      echo -e "$INFO2"Negative"$RESET" test "$INFO2""$test_num""$RESET"
      if [[ $memory -eq 1 ]]; then
        test_memory_output
      else
        test_output
      fi
    fi
  else
    if [[ $verbose -eq 1 ]]; then
      echo Cannot find "$expected" file. # Не найлен файл с эталонным выводом
    fi
  fi
  nt_num=$((nt_num + 1))
done

rm "$out" 2>/dev/null

test_failed=$((fnt_num + fpt_num))

# Вывод результатов тестирования
if [[ $verbose -eq 1 ]]; then
  echo
  if [[ $test_failed -eq 0 ]]; then
    echo -e "$SUCCESS"Testing succesful"$RESET"
  else
    echo -e "$ERROR"Testing failed"$RESET"
  fi

  echo Positive tests: "$((pt_num - fpt_num))" of "$pt_num" passed.
  echo Negative tests: "$((nt_num - fnt_num))" of "$nt_num" passed.
fi

exit $test_failed
