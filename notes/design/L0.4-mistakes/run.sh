#!/usr/bin/env bash
# Builds and runs every deliberately wrong program of the L0.4 mistake catalogue with the course flags and prints what happens.
# *.cpp files are compiled and run (a first-line `// flags:` comment adds compiler flags), *.mjs files run with node,
# *.sh files run with bash (ROOT is the repository root). Output of this script is what the lesson quotes.
# usage: bash run.sh [name ...]   (default: all)
set -uo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"; export ROOT
FLAGS="$(bash "$ROOT/code/shared/cpp/cxxflags.sh" "$HERE")"
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT; export B
names=("$@"); [ ${#names[@]} -eq 0 ] && names=($(cd "$HERE" && ls m*.cpp m*.mjs m*.sh | sed 's/\.[a-z]*$//'))
for n in "${names[@]}"; do
  echo "=== $n"
  if [ -f "$HERE/$n.mjs" ]; then node "$HERE/$n.mjs" 2>&1 | head -${LINES_MAX:-14}; echo "[exit ${PIPESTATUS[0]}]"; continue; fi
  if [ -f "$HERE/$n.sh" ]; then bash "$HERE/$n.sh" 2>&1 | head -${LINES_MAX:-14}; echo "[exit ${PIPESTATUS[0]}]"; continue; fi
  EXTRA="$(sed -n '1s,^// flags: ,,p' "$HERE/$n.cpp")"
  if g++ $FLAGS $EXTRA -I"$ROOT/code/shared/cpp" "$HERE/$n.cpp" -o "$B/$n" 2> "$B/$n.err"; then
    "$B/$n" > "$B/$n.out" 2>&1; code=$?
    head -${LINES_MAX:-14} "$B/$n.out"; echo "[exit $code]"
  else
    echo "[does not compile]"; head -${LINES_MAX:-8} "$B/$n.err"
  fi
done
