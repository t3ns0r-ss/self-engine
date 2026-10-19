#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Checks owners.txt against the headers in tests/.
# Nothing is written into the solution folder.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/shared/uml/uml_check.mjs" ]; do R="$(dirname "$R")"; done
[ -f "$R/code/shared/uml/uml_check.mjs" ] || { echo "code/shared/uml/uml_check.mjs not found" >&2; exit 2; }
UML="node $R/code/shared/uml/uml_check.mjs"
need() { [ -f "$SOL/$1" ] || { echo "$1 not found in $SOL" >&2; exit 1; }; }
need owners.txt
$UML owners "$SOL/owners.txt" "$KIT"/tests/*.hpp
