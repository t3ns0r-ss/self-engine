#!/usr/bin/env bash
set -euo pipefail
DIR="${1:?usage: stress.sh <code-dir> [iterations]}"
N="${2:-2000}"
BUILD="$DIR/.build"
mkdir -p "$BUILD"
for f in solution brute gen; do
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$BUILD/$f" "$DIR/$f.cpp"
done
for ((i = 1; i <= N; i++)); do
  "$BUILD/gen" "$i" > "$BUILD/in.txt"
  "$BUILD/solution" < "$BUILD/in.txt" > "$BUILD/out_solution.txt"
  "$BUILD/brute"    < "$BUILD/in.txt" > "$BUILD/out_brute.txt"
  if ! cmp -s "$BUILD/out_solution.txt" "$BUILD/out_brute.txt"; then
    echo "MISMATCH on seed $i"
    echo "--- input ---";    cat "$BUILD/in.txt"
    echo "--- solution ---"; cat "$BUILD/out_solution.txt"
    echo "--- brute ---";    cat "$BUILD/out_brute.txt"
    exit 1
  fi
done
echo "OK: $N random cases matched"
