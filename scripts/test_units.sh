#!/usr/bin/env bash
set -euo pipefail
ROOT="${1:-code}"
fail=0
while IFS= read -r unit; do
  mkdir -p "$unit/.build"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$unit/.build/solution" "$unit/solution.cpp"
  for in_file in "$unit"/tests/*.in; do
    [ -e "$in_file" ] || continue
    expected="${in_file%.in}.out"
    actual="$unit/.build/actual.out"
    "$unit/.build/solution" < "$in_file" > "$actual"
    if ! diff -q -Z "$actual" "$expected" > /dev/null; then
      echo "FAIL: $in_file"; fail=1
    fi
  done
  if [ -f "$unit/brute.cpp" ] && [ -f "$unit/gen.cpp" ]; then
    bash "$(dirname "$0")/stress.sh" "$unit" 5000 > /dev/null || { echo "STRESS FAIL: $unit"; fail=1; }
  fi
done < <(find "$ROOT" -name solution.cpp -exec dirname {} \; | sort)
[ "$fail" -eq 0 ] && echo "All code units passed" || exit 1
