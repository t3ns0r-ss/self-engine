#!/usr/bin/env bash
# Browser tests for the design components on temporary placeholder topics (DESIGN_TRACKS_PLAN.md Section 11.7).
# Needs Playwright with Chromium (PLAYWRIGHT_PATH to the playwright package if not installed in this project).
set -euo pipefail
cd "$(dirname "$0")/.."
export BASE_PATH=/self-engine/
# Run in a throwaway copy of the repository, so the placeholder topics (which reuse the ids L2.1 and H4.2)
# can never overwrite or delete real lessons. The copy hard-links this project's node_modules.
SRC="$PWD"
WORK="$(mktemp -d)"
tar -C "$SRC" --exclude=./node_modules --exclude=./dist --exclude=./.git --exclude=./work --exclude=./.astro -cf - . | tar -C "$WORK" -xf -
cp -al "$SRC/node_modules" "$WORK/node_modules"   # hard links: no extra space; a symlink breaks Astro's path resolution
cd "$WORK"
cleanup() {
  [ -n "${PREVIEW_PID:-}" ] && kill "$PREVIEW_PID" 2>/dev/null || true
  cd "$SRC"; rm -rf "$WORK"
}
trap cleanup EXIT
CLEAR_REAL=1 node tests/placeholder-design/make.mjs
node scripts/validate.mjs
npx astro build > /dev/null
node scripts/check_built.mjs
./node_modules/.bin/astro preview --port 4329 --ignore-lock > /dev/null 2>&1 &
PREVIEW_PID=$!
for _ in $(seq 1 240); do curl -sf http://localhost:4329/self-engine/ > /dev/null && break; sleep 0.5; done
BASE=http://localhost:4329/self-engine node tests/e2e/design.cjs
