// Writes public/sync-config.json (PROFILE_SYNC_PLAN.md Section 7.3): the same-origin proxy base path when the
// SYNC_PROXY_BASE environment variable is set (self-hosted builds), otherwise null (GitHub Pages builds).
import { writeFileSync } from 'node:fs';

const base = process.env.SYNC_PROXY_BASE || null;
if (base !== null && !/^\/[A-Za-z0-9._~\/-]*$/.test(base)) {
  console.error(`SYNC_PROXY_BASE must be a path such as /sync-proxy, got ${JSON.stringify(base)}`);
  process.exit(1);
}
writeFileSync(new URL('../public/sync-config.json', import.meta.url), JSON.stringify({ proxyBase: base }) + '\n');
console.log(`sync-config.json: proxyBase=${JSON.stringify(base)}`);
