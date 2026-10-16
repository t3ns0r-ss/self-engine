#!/usr/bin/env bash
# Usage: new_attempt.sh <kit-path> [start-from-dir]
#   e.g. new_attempt.sh H5.6/lab/rung-1
#        new_attempt.sh H4.2/lab/rung-3 work/H4.2/lab/rung-2     (continue a ladder from your own previous rung)
# Copies the kit's starter (or start-from-dir) into work/<kit-path>/ (work/ is gitignored) and prints the test command.
set -euo pipefail
K="${1:?usage: new_attempt.sh <kit-path> [start-from-dir]}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC="${2:-$ROOT/exercises/$K/starter}"
DST="$ROOT/work/$K"
[ -f "$ROOT/exercises/$K/test.sh" ] || { echo "no such kit: exercises/$K" >&2; exit 1; }
[ -d "$SRC" ] || { echo "no such folder: $SRC" >&2; exit 1; }
[ -e "$DST" ] && { echo "already exists: work/$K (delete it to start over)" >&2; exit 1; }
mkdir -p "$(dirname "$DST")"
cp -r "$SRC" "$DST"
echo "Edit work/$K, then run:  bash exercises/$K/test.sh work/$K"
