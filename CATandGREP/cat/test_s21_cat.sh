#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
TEST_FILE="test.txt"
LOG_FILE="log.txt"

FLAGS=(-b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank)

> "$LOG_FILE"

run_test() {
  local flags="$1"
  local test_cmd="./s21_cat $flags $TEST_FILE"
  local reference_cmd="cat $flags $TEST_FILE"

  echo ": $test_cmd"
  
  $test_cmd > s21_cat_output.txt 2>/dev/null
  $reference_cmd > cat_output.txt 2>/dev/null

  if diff -q s21_cat_output.txt cat_output.txt > /dev/null; then
    (( COUNTER_SUCCESS++ ))
  else
    echo "$test_cmd" >> "$LOG_FILE"
    (( COUNTER_FAIL++ ))
  fi

  rm -f s21_cat_output.txt cat_output.txt
}

generate_combinations() {
  local array=("$@")
  local n=${#array[@]}

  for ((i=0; i<n; i++)); do
    echo "${array[i]}"
    for ((j=i+1; j<n; j++)); do
      echo "${array[i]} ${array[j]}"
      for ((k=j+1; k<n; k++)); do
        echo "${array[i]} ${array[j]} ${array[k]}"
        for ((l=k+1; l<n; l++)); do
          echo "${array[i]} ${array[j]} ${array[k]} ${array[l]}"
        done
      done
    done
  done
}

while read -r flags; do
  run_test "$flags"
done < <(generate_combinations "${FLAGS[@]}")

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

exit "$COUNTER_FAIL"
