#!/usr/bin/env bash
# Runs one interactive test: the solution and the judge talk to each other through two named pipes.
#   interact.sh <solution-binary> <judge-binary> <hidden-test-file> <verdict-file> [seconds]
# The judge (tests/judge.cpp of a code unit, see code/shared/interact/interact.hpp) writes the verdict file.
# If the judge writes nothing within the time limit (a solution that does not flush its output, or that waits
# for a reply that never comes), both programs are stopped and the verdict is "Idleness limit exceeded".
# The opening order of the pipes is the same on both sides, so the two programs cannot block each other at the start.
set -u
SOL="${1:?usage: interact.sh <solution> <judge> <hidden-test-file> <verdict-file> [seconds]}"
JUDGE="${2:?}"
HIDDEN="${3:?}"
OUT="${4:?}"
SEC="${5:-5}"
DIR="$(mktemp -d)"
trap 'rm -rf "$DIR"' EXIT
mkfifo "$DIR/from_solution" "$DIR/to_solution"
rm -f "$OUT"
timeout "$SEC" "$SOL" > "$DIR/from_solution" < "$DIR/to_solution" 2> /dev/null &
SOL_PID=$!
timeout "$SEC" "$JUDGE" "$HIDDEN" "$OUT" < "$DIR/from_solution" > "$DIR/to_solution" 2> /dev/null
kill "$SOL_PID" 2> /dev/null
wait "$SOL_PID" 2> /dev/null
if [ ! -s "$OUT" ]; then
  echo "Idleness limit exceeded: no verdict within ${SEC} seconds (the solution did not flush its output, or it waits for input that never comes)" > "$OUT"
fi
exit 0
