n_pos=$1
n_neg=$2
n=1

while [[ $n -le $n_pos ]]
do
  touch ./func_tests/data/pos_"$n"_args.txt
  touch ./func_tests/data/pos_"$n"_in.txt
  touch ./func_tests/data/pos_"$n"_out.txt
  n=$((n + 1))
done;

n=1

while [[ $n -le $n_neg ]]
do
  touch ./func_tests/data/neg_"$n"_args.txt
  touch ./func_tests/data/neg_"$n"_in.txt
  touch ./func_tests/data/neg_"$n"_out.txt
  n=$((n + 1))
done;