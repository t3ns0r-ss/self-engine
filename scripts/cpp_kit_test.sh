#!/usr/bin/env bash
# Usage: cpp_kit_test.sh <solution-dir> <tests-dir>
# Builds every .cpp under <solution-dir> (the learner's or reference's code, no main) together with every .cpp in
# <tests-dir> (one of them defines MINI_TEST_MAIN) and runs the result. Exit 0 = all tests pass.
# A kit's test.sh is one line:  bash "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)/scripts/cpp_kit_test.sh" "$1" "$(dirname "$0")/tests"
set -euo pipefail
SOL="$(cd "${1:?usage: cpp_kit_test.sh <solution-dir> <tests-dir>}" && pwd)"
TESTS="$(cd "${2:?usage: cpp_kit_test.sh <solution-dir> <tests-dir>}" && pwd)"
HERE="$(cd "$(dirname "$0")" && pwd)"
STD="${CXX_STD:-c++17}"
bin="$(mktemp)"; trap 'rm -f "$bin"' EXIT
mapfile -t srcs < <(find "$SOL" "$TESTS" -name '*.cpp' | sort)
g++ -std="$STD" -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-sanitize-recover=undefined -I "$SOL" -I "$SOL/src" -I "$HERE/../code/_shared" "${srcs[@]}" -o "$bin"
"$bin"
