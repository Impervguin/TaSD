#!/bin/bash

OK=0 # Только для данных, без проверки памяти - успех

MEMORY_OUTPUT=0   # Память - успех, данные - успех
NMEMORY_OUTPUT=2  # Память - провал, данные - успех
NMEMORY_NOUTPUT=3 # Память - успех, данные - провал
MEMORY_NOUTPUT=4  # Память - провал, данные - провал

# Путь к тестам и скриптам из папки проекта
PATH_TO_DATA="./func_tests/data"
PATH_TO_BDATA="./func_tests/bin_data"
PATH_TO_SCRIPTS="./func_tests/scripts/"
FILE_OUT="./func_tests/out_file"

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

# Функция для вывода информации о тесте
function test_output {
  if [[ $rc -eq $OK ]]; then
    echo -e Test: "$SUCCESS"passed"$RESET"
  else
    echo -e Test: "$ERROR"failed"$RESET"
    echo -e Input: "$INFO2""$(cat "$in_f")""$RESET"
    echo -e Expected output: "$INFO2""$(cat "$exp_f")""$RESET"
    echo -e Output: "$INFO2""$(cat "$FILE_OUT")""$RESET"
  fi
}
# Функция для вывода информации о тесте с проверкой памяти
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
    echo -e Input: "$INFO2""$(cat "$in_f")""$RESET"
    echo -e Expected output: "$INFO2""$(cat "$exp_f")""$RESET"
    echo -e Output: "$INFO2""$(cat "$FILE_OUT")""$RESET"
  fi
}

# Ввод ключей
for param in "$@"; do
  if [[ $param == "-v" ]] || [[ $param == "--verbose" ]]; then # Ключ вывода работы программы
    verbose=1
  elif [[ $param == "--mem-check" ]]; then # Ключ проверки памяти с valgrind
    memory=1
    key_mem="--mem-check"
  elif [[ $param == "-b2t" ]]; then # Ключ возможного перевода вывода из бинарного вида в текстовый
    B2T=1
  elif [[ $param == "-t2b" ]]; then # Ключ возможного перевода ввода из текстового вида в двоичный
    T2B=1
  elif [[ $param == "-csf" ]]; then # Ключ, показывающий, что меняется исходный файл
    CSF=1
  fi
  shift
done

out=$(mktemp) # Файл для выхода программы
# Позитивное тестирование
for args in "$PATH_TO_DATA"/pos_[0-9][0-9]_args.txt; do # Проходимся по всем входным тестам
  b_out= # Флаг показывающий, что вывод будет в бинарном виде
  b_in= # Флаг показывающий, что ввод будет в бинарном виде

  if [[ "$args" == "$PATH_TO_DATA/pos_[0-9][0-9]_args.txt" ]]; then
    echo -e "$args""No positive tests found""$RESET"
    break
  fi

  test_num=$(echo "$args" | grep -o "[0-9][0-9]") # Номер позитивного теста
  input=$PATH_TO_DATA/pos_"$test_num"_in.txt # Файл ввода
  expected=$PATH_TO_DATA/pos_"$test_num"_out.txt # Файл с эталонным выводом


  if [[ ! -f $args ]]; then
    echo -e "$INFO2""No positive test $test_num args found""$RESET"
    continue
  fi

 # Если нет файла ввода и включен флаг перевода, то ищем в bin_data ввод
  if [[ ! -f $input ]] && [[ $T2B -eq 1 ]]; then
    binput=$PATH_TO_BDATA/pos_"$test_num"_in.txt;
    if [[ -f $binput ]]; then # Если он существует
      ./func_tests/scripts/b2t.exe t2b "$binput" "$input" # То переводим в двоичный вид и помещаем в data
      in_f=$binput # Текстовый ввод в bin_data
      b_in=1 # Ввод в бинарном виде
    else
      echo -e "$INFO2""No positive test $test_num input found""$RESET"
      continue
    fi
  elif [[ -f $input ]]; then
    in_f=$input
  else
    echo -e "$INFO2""No positive test $test_num input found""$RESET"
    continue
  fi

  # Если нет файла вывода и включен флаг перевода, то ищем в bin_data вывод
  if [[ ! -f $expected ]] && [[ $B2T -eq 1 ]]; then
      bexpected=$PATH_TO_BDATA/pos_"$test_num"_out.txt;
      if [[ -f $bexpected ]]; then # Если он существует
        b_out=1 # Вывод в бинарном виде
        exp_f=$bexpected # Текстовый вывод в bin_data
      else
        echo -e "$INFO2""No positive test $test_num output found""$RESET"
        continue
      fi
    elif [[ -f $expected ]]; then
      exp_f=$expected
    elif [[ ! -f $expected ]]; then
      echo -e "$INFO2""No positive test $test_num output found""$RESET"
      continue
  fi
  # Ввод в бинарном виде

  if [[ -n $CSF ]]; then
    csf="-csf"
  else
    csf=""
  fi

  # Тестируем
  if [[ -n $b_out ]]; then
    bash "$PATH_TO_SCRIPTS"pos_case.sh "$args" "$input" "$bexpected" "$key_mem" --out="$out" -b2t "$csf"
  else
    bash "$PATH_TO_SCRIPTS"pos_case.sh "$args" "$input" "$expected" "$key_mem" --out="$out" "$csf"
  fi
  rc=$?
#  echo $rc
  # Если ввод был бинарный, то этот двоичный файл нужно удалить
  if [[ -n $b_in ]]; then
    rm "$input"
  fi
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
  pt_num=$((pt_num + 1))
  cat /dev/null > $FILE_OUT
done

# Негативное тестирование
for args in "$PATH_TO_DATA"/neg_[0-9][0-9]_args.txt; do # Проходимся по всем входным тестам
  b_out= # Флаг показывающий, что вывод будет в бинарном виде
  b_in= # Флаг показывающий, что ввод будет в бинарном виде

  if [[ "$args" == "$PATH_TO_DATA/neg_[0-9][0-9]_args.txt" ]]; then
    echo -e "$args""No negative tests found""$RESET"
    break
  fi

  test_num=$(echo "$args" | grep -o "[0-9][0-9]") # Номер позитивного теста
  input=$PATH_TO_DATA/neg_"$test_num"_in.txt # Файл с вводом
  expected=$PATH_TO_DATA/neg_"$test_num"_out.txt # Файл с эталонным выводом


  if [[ ! -f $args ]]; then
    echo -e "$INFO2""No negative test $test_num args found""$RESET"
    continue
  fi

  # Если нет файла ввода и включен флаг перевода, то ищем в bin_data ввод
  if [[ ! -f $input ]] && [[ $T2B -eq 1 ]]; then
    binput=$PATH_TO_BDATA/neg_"$test_num"_in.txt;
    if [[ -f $binput ]]; then # Если он существует
      ./func_tests/scripts/b2t.exe t2b "$binput" "$input" # То переводим в двоичный вид и помещаем в data
      in_f=$binput # Текстовый ввод в bin_data
      b_in=1 # Ввод в бинарном виде
    else
      echo -e "$INFO2""No negative test $test_num input found""$RESET"
      continue
    fi
  elif [[ -f $input ]]; then
    in_f=$input
  else
    echo -e "$INFO2""No negative test $test_num input found""$RESET"
    continue
  fi

  if [[ -n $CSF ]]; then
    csf="-csf"
  else
    csf=""
  fi

  #Тестируем
  if [[ -n $b_out ]]; then
    bash "$PATH_TO_SCRIPTS"neg_case.sh "$args" "$input" "$key_mem" --out="$out" -b2t "$csf"
  else
    bash "$PATH_TO_SCRIPTS"neg_case.sh "$args" "$input" "$key_mem" --out="$out" "$csf"
  fi
  rc=$?
#  echo $rc
  # Если код возврата не соответствует OK, тест не прошел по памяти или по данным
  if [[ -n $b_in ]]; then
    rm "$input"
  fi

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
