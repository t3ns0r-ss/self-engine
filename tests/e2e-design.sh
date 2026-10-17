#!/usr/bin/env bash
# Browser tests for the design components on temporary placeholder topics (DESIGN_TRACKS_PLAN.md Section 11.7).
# Needs Playwright with Chromium (PLAYWRIGHT_PATH to the playwright package if not installed in this project).
set -euo pipefail
cd "$(dirname "$0")/.."
export BASE_PATH=/self-engine/
cleanup() {
  [ -n "${PREVIEW_PID:-}" ] && kill "$PREVIEW_PID" 2>/dev/null || true
  node tests/placeholder-design/make.mjs --remove
}
trap cleanup EXIT
node tests/placeholder-design/make.mjs
node scripts/validate.mjs
npx astro build > /dev/null
node scripts/check_built.mjs
./node_modules/.bin/astro preview --port 4329 --ignore-lock > /dev/null 2>&1 &
PREVIEW_PID=$!
for _ in $(seq 1 60); do curl -sf http://localhost:4329/self-engine/ > /dev/null && break; sleep 0.5; done
BASE=http://localhost:4329/self-engine node tests/e2e/design.cjs
