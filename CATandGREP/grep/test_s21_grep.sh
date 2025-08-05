 #!/usr/bin/env bash

pass=0
fail=0

filesarr=("test1.txt" "test2.txt" "teest.txt")
options=("i" "v" "c" "l" "n" "h" "s" "o")
patterns=("-e vga" "-e o" "-f reg1.txt" "-f reg2.txt")

compare_output() {
    local args="$1"
    local pattern="$2"
    local file="$3"
    echo "test -$args $pattern $file"
    local mine=$(./s21_grep -$args $pattern $file 2>/dev/null)
    local they=$(grep -$args $pattern $file 2>/dev/null)
    if diff <(echo "$mine") <(echo "$they") &>/dev/null; then
        ((pass++))
    else
        echo "FAIL: grep -$args \"$pattern\" $file"
        ((fail++))
    fi
}

for opt in "${options[@]}"; do
    for file in "${filesarr[@]}"; do
        for pattern in "${patterns[@]}"; do
            compare_output "$opt" "$pattern" "$file"
        done
    done
done

for ((i = 0; i < ${#options[@]}; i++)); do
    for ((j = i + 1; j < ${#options[@]}; j++)); do
        combo="${options[i]}${options[j]}"
        for file in "${filesarr[@]}"; do
            for pattern in "${patterns[@]}"; do
                compare_output "$combo" "$pattern" "$file"
            done
        done
    done
done

echo "Pass: $pass"
echo "Fail: $fail"