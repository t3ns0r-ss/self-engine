#!/usr/bin/env bash
# Usage: cxxflags.sh <unit-or-kit-dir>
# Prints the g++ flags every C++ unit and kit uses. The one switch: a file named "sanitizer" in that folder,
# containing the word "thread", selects the thread sanitizer (concurrency units and kits, Phase L6);
# without the file, the address and undefined-behaviour sanitizers are used. The two cannot be combined.
set -euo pipefail
D="${1:?usage: cxxflags.sh <dir>}"
BASE="-std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Werror -pthread -fno-sanitize-recover=all"
SAN="-fsanitize=address,undefined"
if [ -f "$D/sanitizer" ]; then
  case "$(tr -d '[:space:]' < "$D/sanitizer")" in
    thread) SAN="-fsanitize=thread" ;;
    *) echo "cxxflags.sh: $D/sanitizer must contain the word: thread" >&2; exit 2 ;;
  esac
fi
echo "$BASE $SAN"
