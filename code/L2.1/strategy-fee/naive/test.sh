#!/usr/bin/env bash
# usage: bash test.sh <dir>   Builds and runs the unit's tests.cpp (and checks that main.cpp compiles and runs) in <dir>.
set -euo pipefail
D="$(cd "$1" && pwd)"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
S="$HERE"; while [ "$S" != "/" ] && [ ! -f "$S/shared/cpp/check.hpp" ]; do S="$(dirname "$S")"; done
[ -f "$S/shared/cpp/check.hpp" ] || { echo "code/shared/cpp/check.hpp not found" >&2; exit 2; }
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
FLAGS="$(bash "$S/shared/cpp/cxxflags.sh" "$HERE")"
g++ $FLAGS -I"$S/shared/cpp" -I"$D" "$D/tests.cpp" -o "$B/tests"
g++ $FLAGS -I"$D" "$D/main.cpp" -o "$B/main"
"$B/tests"
"$B/main" > /dev/null
