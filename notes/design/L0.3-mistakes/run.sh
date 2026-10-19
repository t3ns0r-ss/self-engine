#!/usr/bin/env bash
# Builds and runs every deliberately wrong program of the L0.3 mistake catalogue with the course flags and prints what happens.
# usage: bash run.sh [name ...]   (default: all)  Output of this script is what the lesson quotes.
set -uo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
FLAGS="$(bash "$ROOT/code/shared/cpp/cxxflags.sh" "$HERE")"
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
names=("$@"); [ ${#names[@]} -eq 0 ] && names=($(cd "$HERE" && ls *.cpp | sed 's/\.cpp$//'))
for n in "${names[@]}"; do
  echo "=== $n"
  EXTRA="$(sed -n '1s,^// flags: ,,p' "$HERE/$n.cpp")"
  if g++ $FLAGS $EXTRA -I"$ROOT/code/shared/cpp" "$HERE/$n.cpp" -o "$B/$n" 2> "$B/$n.err"; then
    "$B/$n" > "$B/$n.out" 2>&1; code=$?
    head -${LINES_MAX:-14} "$B/$n.out"; echo "[exit $code]"
  else
    echo "[does not compile]"; head -${LINES_MAX:-8} "$B/$n.err"
  fi
done
