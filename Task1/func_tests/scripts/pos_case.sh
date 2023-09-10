#!/bin/bash
# Константы кодов возврата
OK=0 # Только для данных, без проверки памяти - успех

MEMORY_OUTPUT=0   # Память - успех, данные - успех
NMEMORY_OUTPUT=2  # Память - провал, данные - успех
NMEMORY_NOUTPUT=3 # Память - успех, данные - провал
MEMORY_NOUTPUT=4  # Память - провал, данные - провал

WRONG_OUTPUT=5 # Только для данных, без проверки памяти - провал
TEST_NOT_FOUND_ERROR=6
APP_NOT_FOUND_ERROR=7
OUT_ERROR=8

FILE_OUT="./func_tests/out_file"
APP="./app.exe"

# Анализ полученых ключей и файлов
for param in "$@"; do
  if [[ $param == "--mem-check" ]]; then # Ключ проверки памяти с valgrind
    mem_check=1
  elif [[ $param =~ ^--out=.*$ ]]; then
    out=${param##*"="}
  elif [[ $param == "-b2t" ]]; then
    b2t=1
  elif [[ $param == "-csf" ]]; then
    csf=1
  elif [[ -z $args ]]; then
    args=$param
  elif [[ -z $input ]]; then
    input=$param
  elif [[ -z $expected ]]; then
    expected=$param
  fi
done


# Проверка введенных файлов

if [[ ! -f "$args" ]]; then
  exit $TEST_NOT_FOUND_ERROR
fi

if [[ ! -f "$expected" ]]; then
  exit $TEST_NOT_FOUND_ERROR
fi
# Проверка на наличие скомпилированного исходника
if [[ ! -f $APP ]]; then
  exit $APP_NOT_FOUND_ERROR
fi

if [[ -n "$out" &&  ( ! -f "$out" || ! -r "$out" )  ]]; then
  exit $OUT_ERROR
fi
# Файл для вывода программы
if [[ -z $out ]]; then
  out=$(mktemp)
  out_tmp=1
fi
# Файл для вывода valgrind

mem_check_out=$(mktemp)

if [[ -n $mem_check ]]; then
  # Запуска теста с проверкой на утечки памяти
  valgrind --leak-check=yes --leak-resolution=med -q --log-file="$mem_check_out" "$APP" < "$(cat "$args")" >"$out"
  rc=$?
  # Если файл не пустой, значит valgrind нашел утечку
  if [[ -n $(cat "$mem_check_out") ]]; then
    mem_passed=1 # Память - успех
  else
    mem_passed=0 # Память - провал
  fi
else
  # shellcheck disable=SC2046
  "$APP" $(cat "$args") > "$out" # Пока не разобрался, но если выражение обрамить кавычками, то программа не работает
  rc=$?
fi

# Если вывод программы пустой, значит вывод программы происходит в файл (out_file)
if [[ ! -s "$out"  && $rc -eq 0 ]]; then
  out=$FILE_OUT
  # Если задан ключ -csf, значит программа модифицирует входной файл
  if [[ -n "$csf" ]]; then
    cp "$input" "$out" # Копируем модифицированный файл в вывод
  fi
else
  prog_out=1 # Выход выдала программа в stdout
  cp $out $FILE_OUT # Копируем этот выход в out_file, чтобы выход программы всегда был в нем
fi



# Если подан ключ -b2t, значит выход программы получен в двоичном виде
if [[ -n $b2t && -z $prog_out ]]; then
  tmp=$(mktemp)
  cp "$out" "$tmp" # Копируем двоичный выход
  ./func_tests/scripts/b2t.exe b2t "$tmp" "$out" # Переводим выход в текстовый формат
  rm "$tmp"
fi

# Сравнение ожидаемого вывода и полученного с помощью компаратора
func_tests/scripts/comparator.sh "$out" "$expected" # Сравниваем текстовый выход с ожидаемым
data_passed=$?
if [[ $data_passed -eq 0 ]] && [[ $rc -eq 0 ]]; then
  test_passed=0 # Тесты - успех
else
  test_passed=1 # Тесты - провал
fi

# Удаление временных файлов
if [[ -n $out_tmp ]]; then
  rm "$out" 2>/dev/null
fi
rm "$mem_check_out" 2>/dev/null

# Возврат результатов тестирования
if [[ -n "$mem_check" ]]; then
  if [[ "$mem_passed" -eq 0 ]] && [[ "$test_passed" -eq 0 ]]; then
    result="$MEMORY_OUTPUT"
  elif [[ "$mem_passed" -eq 1 ]] && [[ "$test_passed" -eq 0 ]]; then
    result="$NMEMORY_OUTPUT"
  elif [[ "$mem_passed" -eq 1 ]] && [[ "$test_passed" -eq 1 ]]; then
    result="$NMEMORY_NOUTPUT"
  elif [[ "$mem_passed" -eq 0 ]] && [[ "$test_passed" -eq 1 ]]; then
    result="$MEMORY_NOUTPUT"
  fi
else
  if [[ "$test_passed" -eq 0 ]]; then
    result="$OK"
  else
    result="$WRONG_OUTPUT"
  fi
fi
exit "$result"
