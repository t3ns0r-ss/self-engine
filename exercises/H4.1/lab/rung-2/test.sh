#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Runs the kit's tests (with the race detector) against the
# solution's non-test .go files, in a throwaway module, so the learner's folder is never modified.
# The throwaway module uses the same Go version as the repository's code/go.mod.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/go.mod" ]; do R="$(dirname "$R")"; done
GOV="$(sed -n 's/^go //p' "$R/code/go.mod")"
[ -n "$GOV" ] || { echo "code/go.mod not found or has no go line" >&2; exit 2; }
W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
find "$SOL" -maxdepth 1 -name '*.go' ! -name '*_test.go' -exec cp {} "$W"/ \;
cp "$KIT"/tests/*_test.go "$W"/
printf 'module kit\n\ngo %s\n' "$GOV" > "$W/go.mod"
cd "$W"
go vet ./...
go test -race -count=1 ./...
