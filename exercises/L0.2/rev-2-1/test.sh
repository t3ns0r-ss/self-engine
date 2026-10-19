#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Builds tests/tests.cpp with the solution's headers and .cpp files,
# using the flags from code/shared/cpp/cxxflags.sh (this kit's "sanitizer" file, if any, picks the sanitizer),
# then runs it. Nothing is written into the solution folder.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/shared/cpp/check.hpp" ]; do R="$(dirname "$R")"; done
[ -f "$R/code/shared/cpp/check.hpp" ] || { echo "code/shared/cpp/check.hpp not found" >&2; exit 2; }
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
mapfile -t SRCS < <(find "$SOL" -maxdepth 1 -name '*.cpp' ! -name 'main.cpp')
g++ $(bash "$R/code/shared/cpp/cxxflags.sh" "$KIT") -I"$R/code/shared/cpp" -I"$SOL" "$KIT/tests/tests.cpp" "${SRCS[@]}" -o "$B/tests"
"$B/tests"
