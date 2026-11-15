#!/usr/bin/env bash
set -euo pipefail
DIR="${1:?usage: stress.sh <code-dir> [iterations]}"
N="${2:-2000}"
BUILD="$DIR/.build"
mkdir -p "$BUILD"
if [ -f "$DIR/tests/judge.cpp" ]; then
  # Interactive unit (DEVELOPER_GUIDE.md, "Interactive code units"): no brute force; the judge checks every run.
  HERE="$(cd "$(dirname "$0")" && pwd)"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$BUILD/solution" "$DIR/solution.cpp"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$BUILD/gen" "$DIR/gen.cpp"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$BUILD/judge" "$DIR/tests/judge.cpp"
  for ((i = 1; i <= N; i++)); do
    "$BUILD/gen" "$i" > "$BUILD/in.txt"
    bash "$HERE/interact.sh" "$BUILD/solution" "$BUILD/judge" "$BUILD/in.txt" "$BUILD/verdict.txt" 4
    if ! head -n 1 "$BUILD/verdict.txt" | grep -q '^OK'; then
      echo "FAILED on seed $i"
      echo "--- hidden test ---";            cat "$BUILD/in.txt"
      echo "--- verdict and transcript ---"; cat "$BUILD/verdict.txt"
      exit 1
    fi
  done
  echo "OK: $N random cases matched"
  exit 0
fi
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
