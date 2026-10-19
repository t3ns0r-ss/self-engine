#!/usr/bin/env bash
# usage: bash test.sh <dir>   Builds and runs the unit's tests.cpp against the code in <dir>, then checks the unit's diagrams.
set -euo pipefail
D="$(cd "$1" && pwd)"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
S="$HERE"; while [ "$S" != "/" ] && [ ! -f "$S/shared/cpp/check.hpp" ]; do S="$(dirname "$S")"; done
[ -f "$S/shared/cpp/check.hpp" ] || { echo "code/shared/cpp/check.hpp not found" >&2; exit 2; }
UML="node $S/shared/uml/uml_check.mjs"
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
mapfile -t SRCS < <(find "$D" -maxdepth 1 -name '*.cpp' ! -name 'tests.cpp' ! -name 'main.cpp')
g++ $(bash "$S/shared/cpp/cxxflags.sh" "$HERE") -I"$S/shared/cpp" -I"$D" "$D/tests.cpp" "${SRCS[@]}" -o "$B/tests"
"$B/tests"
diff <($UML extract "$D/checked_first.hpp") <($UML extract "$D/mailed_first.hpp") > /dev/null   # the class diagrams are identical
[ -n "$($UML extract "$D/checked_first.hpp")" ]
