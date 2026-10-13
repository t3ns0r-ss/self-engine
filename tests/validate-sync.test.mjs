import test from 'node:test';
import assert from 'node:assert/strict';
import { checkAliases, checkStatusReads, checkSyncConfig, checkSnippetSlugs } from '../src/lib/validate-sync.mjs';
import { buildAliases, parallelContests } from '../scripts/cf_aliases.mjs';

test('Y1: every site key needs an alias entry (an empty list is fine)', () => {
  assert.deepEqual(checkAliases(['1A', '2B'], { '1A': [], '2B': ['3C'] }), []);
  const e = checkAliases(['1A', '2B'], { '1A': [] });
  assert.equal(e.length, 1);
  assert.match(e[0], /node scripts\/cf_aliases\.mjs/);
});

test('Y2: direct status reads are rejected outside the allowed files', () => {
  const bad = [{ path: 'src/components/X.tsx', text: 'const a = logs[p.id]?.status;\nconst b = log.status;' }];
  assert.equal(checkStatusReads(bad).length, 2);
  assert.equal(checkStatusReads([{ path: 'src/components/LogPanel.tsx', text: 'log?.status' }]).length, 0);
  assert.equal(checkStatusReads([{ path: 'src/lib/sync/status.ts', text: 'local.status' }]).length, 0);
  assert.equal(checkStatusReads([{ path: 'src/components/X.tsx', text: 'st(p.id).status; view.status; r.status' }]).length, 0);
});

test('Y3: sync-config.json', () => {
  assert.deepEqual(checkSyncConfig('{"proxyBase":null}', {}), []);
  assert.deepEqual(checkSyncConfig('{"proxyBase":"/sync-proxy"}', { SYNC_PROXY_BASE: '/sync-proxy' }), []);
  assert.equal(checkSyncConfig('{"proxyBase":"/x"}', {}).length, 1);
  assert.equal(checkSyncConfig('', {}).length, 1);
  assert.equal(checkSyncConfig('{}', {}).length, 1);
});

test('Y4: snippet text must not name reserved slugs', () => {
  assert.deepEqual(checkSnippetSlugs('fetch two-sum', new Set(['lru-cache'])), []);
  assert.equal(checkSnippetSlugs('fetch lru-cache', new Set(['lru-cache'])).length, 1);
});

test('aliases: twins are same-name problems in a contest with the same start time', () => {
  const contests = [
    { id: 1500, startTimeSeconds: 100 }, { id: 1501, startTimeSeconds: 100 }, { id: 1502, startTimeSeconds: 200 },
  ];
  const probs = {
    1500: [{ index: 'A', name: 'Going Home' }, { index: 'B', name: 'Two chandeliers' }],
    1501: [{ index: 'A', name: 'Alexey and Train' }, { index: 'C', name: 'Going Home' }],
    1502: [{ index: 'A', name: 'Going Home' }], // same name, different time: not a twin
  };
  const out = buildAliases(['1500A', '1501C', '1500B', '1502A'], contests, (id) => probs[id] ?? []);
  assert.deepEqual(out, { '1500A': ['1501C'], '1501C': ['1500A'], '1500B': [], '1502A': [] });
  assert.deepEqual(parallelContests(['1500A'], contests), [1500, 1501]);
  assert.deepEqual(parallelContests(['1502A'], contests), []);
});
