#!/usr/bin/env bash
# Usage: test_design.sh [code-root]   (default: code)
# Runs every design code unit under the root:
#   1. claim/calc units: check.py or calc.py; stdout must equal expected.txt exactly
#   2. pattern units (unit.yaml with "kind: pattern"): change_cost.sh stdout must equal measured-<variant>.tsv
#   3. C++ solution units (cpp-unit.yaml): g++ build with sanitizers, run tests   (edit this block if lld_language changes; see Section 3)
set -euo pipefail
ROOT="${1:-code}"
HERE="$(cd "$(dirname "$0")" && pwd)"
fail=0

while IFS= read -r f; do
  d="$(dirname "$f")"
  if [ ! -f "$d/expected.txt" ]; then echo "MISSING expected.txt: $d"; fail=1; continue; fi
  if ! python3 -I "$f" | diff -q - "$d/expected.txt" > /dev/null; then echo "FAIL (output differs from expected.txt): $d"; fail=1; fi
done < <(find "$ROOT" \( -name check.py -o -name calc.py \) | sort)

while IFS= read -r y; do
  d="$(dirname "$y")"
  grep -q '^kind: pattern' "$y" || continue
  variants="$(sed -n 's/^variants: \[\(.*\)\]/\1/p' "$y" | tr -d ' ' | tr ',' ' ')"
  [ -n "$variants" ] || { echo "MISSING variants in $y"; fail=1; continue; }
  for v in $variants; do
    out="$(mktemp)"; err="$(mktemp)"
    if ! bash "$HERE/change_cost.sh" "$d/$v" > "$out" 2> "$err"; then echo "FAIL (change_cost): $d/$v"; cat "$err"; fail=1
    elif ! diff -q "$out" "$d/measured-$v.tsv" > /dev/null; then echo "FAIL (measured-$v.tsv is out of date): $d"; fail=1; fi
    rm -f "$out" "$err"
  done
done < <(find "$ROOT" -name unit.yaml | sort)

CXX_STD="${CXX_STD:-c++17}"
SHARED="$HERE/../code/_shared"
while IFS= read -r m; do
  d="$(dirname "$m")"
  srcs=(); shopt -s nullglob; srcs=("$d"/src/*.cpp "$d"/tests/*.cpp); shopt -u nullglob
  if [ ! -d "$d/tests" ] || ! ls "$d"/tests/*.cpp > /dev/null 2>&1; then echo "MISSING tests/*.cpp: $d"; fail=1; continue; fi
  bin="$(mktemp)"; log="$(mktemp)"
  sans="-fsanitize=address,undefined -fno-sanitize-recover=undefined"
  if ! g++ -std="$CXX_STD" -O2 -g -Wall -Wextra -Werror $sans -I "$d/src" -I "$SHARED" "${srcs[@]}" -o "$bin" > "$log" 2>&1; then
    echo "FAIL (build): $d"; cat "$log"; fail=1
  elif ! "$bin" > "$log" 2>&1; then
    echo "FAIL (tests): $d"; cat "$log"; fail=1
  elif grep -q '^thread_sanitizer: true' "$m"; then
    if ! g++ -std="$CXX_STD" -O1 -g -Wall -Wextra -Werror -fsanitize=thread -I "$d/src" -I "$SHARED" "${srcs[@]}" -o "$bin" > "$log" 2>&1 || ! "$bin" > "$log" 2>&1; then
      echo "FAIL (thread sanitizer): $d"; cat "$log"; fail=1
    fi
  fi
  rm -f "$bin" "$log"
done < <(find "$ROOT" -name cpp-unit.yaml | sort)

[ "$fail" -eq 0 ] && echo "All design code units passed" || exit 1
