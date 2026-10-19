#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Checks decision.txt: no diagram is needed, and one short sentence names both classes.
# Nothing is written into the solution folder.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/shared/uml/uml_check.mjs" ]; do R="$(dirname "$R")"; done
[ -f "$R/code/shared/uml/uml_check.mjs" ] || { echo "code/shared/uml/uml_check.mjs not found" >&2; exit 2; }
UML="node $R/code/shared/uml/uml_check.mjs"
need() { [ -f "$SOL/$1" ] || { echo "$1 not found in $SOL" >&2; exit 1; }; }
need decision.txt
$UML lines "$SOL/decision.txt" "$KIT/tests/expected.txt" > /dev/null
S="$(grep -i '^sentence:' "$SOL/decision.txt" | head -1 | sed 's/^[^:]*:[[:space:]]*//')"
[ -n "$S" ] || { echo "decision.txt has no sentence: line" >&2; exit 1; }
N="$(echo "$S" | wc -w)"
[ "$N" -le 25 ] || { echo "the sentence has $N words; 25 at most" >&2; exit 1; }
for c in $(cat "$KIT/tests/must_name"); do echo "$S" | grep -qw "$c" || { echo "the sentence does not name $c" >&2; exit 1; }; done
