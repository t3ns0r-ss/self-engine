#!/usr/bin/env bash
# Builds the site and uploads it to the server in .env.deploy (PLAN.md Section 14.2).
# Aborts before uploading if the code tests or the build fail, so a broken build never
# replaces a working site.
set -euo pipefail
cd "$(dirname "$0")/.."
if [ ! -f .env.deploy ]; then
  echo "Missing .env.deploy: copy .env.deploy.example and fill it in." >&2
  exit 1
fi
set -a
# shellcheck disable=SC1091
. ./.env.deploy
set +a
: "${DEPLOY_HOST:?DEPLOY_HOST is not set in .env.deploy}"
: "${DEPLOY_PATH:?DEPLOY_PATH is not set in .env.deploy}"
: "${SITE_URL:?SITE_URL is not set in .env.deploy}"

bash scripts/test_units.sh code
SITE_URL="$SITE_URL" npm run build
rsync -az --delete dist/ "$DEPLOY_HOST:$DEPLOY_PATH/"
echo "Deployed to $SITE_URL"
