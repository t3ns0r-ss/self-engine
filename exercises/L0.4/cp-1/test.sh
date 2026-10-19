#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Checks diagram.mmd against the headers and sequence.mmd against the recorded calls of tests/model.cpp.
# Nothing is written into the solution folder.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/shared/uml/uml_check.mjs" ]; do R="$(dirname "$R")"; done
[ -f "$R/code/shared/uml/uml_check.mjs" ] || { echo "code/shared/uml/uml_check.mjs not found" >&2; exit 2; }
UML="node $R/code/shared/uml/uml_check.mjs"
need() { [ -f "$SOL/$1" ] || { echo "$1 not found in $SOL" >&2; exit 1; }; }
need diagram.mmd; need sequence.mmd
$UML classes "$SOL/diagram.mmd" "$KIT"/tests/*.hpp
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
g++ $(bash "$R/code/shared/cpp/cxxflags.sh" "$KIT") -I"$KIT/tests" "$KIT/tests/model.cpp" -o "$B/model"
TRACE_DIR="$B" "$B/model" > /dev/null
for s in $(cat "$KIT/tests/scenarios"); do
  echo "scenario $s" >&2
  $UML sequence "$SOL/sequence.mmd" "$B/$s.txt"
done
