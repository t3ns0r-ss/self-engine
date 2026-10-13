// Runs the profile-sync build checks Y1 to Y4 (PROFILE_SYNC_PLAN.md Section 15) over the real files.
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join } from 'node:path';
import { parse } from 'yaml';
import { checkAliases, checkSnippetSlugs, checkStatusReads, checkSyncConfig } from '../src/lib/validate-sync.mjs';
import { leetCodeSnippet } from '../src/lib/sync/snippet.ts';
import { siteCfKeys } from './cf_aliases.mjs';

const ROOT = new URL('..', import.meta.url).pathname;
const errors = [];

const aliasPath = join(ROOT, 'src/data/sync/cf-aliases.json');
errors.push(...checkAliases(siteCfKeys(ROOT), existsSync(aliasPath) ? JSON.parse(readFileSync(aliasPath, 'utf8')) : {}));

const files = [];
for (const f of readdirSync(join(ROOT, 'src'), { recursive: true }).map(String)) {
  if (/\.(tsx?|astro)$/.test(f)) files.push({ path: `src/${f}`, text: readFileSync(join(ROOT, 'src', f), 'utf8') });
}
errors.push(...checkStatusReads(files));

const cfgPath = join(ROOT, 'public/sync-config.json');
errors.push(...checkSyncConfig(existsSync(cfgPath) ? readFileSync(cfgPath, 'utf8') : '', process.env));

// Y4: the LeetCode snippet names no reserved LeetCode problem (drill, look-alike, checkpoint, review, exam).
const reserved = new Set();
for (const f of readdirSync(join(ROOT, 'src/data/bank'))) {
  if (!f.endsWith('.yaml')) continue;
  for (const p of parse(readFileSync(join(ROOT, 'src/data/bank', f), 'utf8')).problems ?? []) if (p.set === 'reserved' && p.id.startsWith('lc-')) reserved.add(p.id.slice(3));
}
for (const f of readdirSync(join(ROOT, 'src/data/topics'))) {
  if (!f.endsWith('.yaml')) continue;
  for (const p of parse(readFileSync(join(ROOT, 'src/data/topics', f), 'utf8')).problems ?? []) if (p.id.startsWith('lc-') && !['ladder', 'worked_example'].includes(p.role)) reserved.add(p.id.slice(3));
}
errors.push(...checkSnippetSlugs(leetCodeSnippet('https://example.com/profiles/', 'someone'), reserved));

if (errors.length) {
  console.error(errors.map((e) => `sync check: ${e}`).join('\n'));
  process.exit(1);
}
console.log(`Profile sync checks passed (Y1 aliases, Y2 status reads, Y3 sync-config, Y4 snippet; ${reserved.size} reserved LeetCode slugs).`);
