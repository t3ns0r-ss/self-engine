import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { makeGate, newCounters, syncCf, syncAc, verifyCfHandle, totalTries } from '../src/lib/sync/platforms.ts';
import { parseImportText, decodeLcFragment, MAX_IMPORT_BYTES } from '../src/lib/sync/leetcode.ts';
import { cfUserStatus, acSubmissions } from '../src/lib/sync/schemas.ts';

const fx = (n) => JSON.parse(readFileSync(new URL(`./sync/fixtures/${n}`, import.meta.url), 'utf8'));
const clock = () => { let t = 0; return { now: () => t, sleep: async (ms) => { t += ms; } }; };
const net = (fetchFn) => { const c = clock(); return { gate: makeGate('cf', c), transport: { fetch: fetchFn }, sleep: c.sleep }; };
const resp = (body, status = 200) => ({ ok: status < 400, status, json: async () => body });

test('recorded fixtures parse with the zod schemas', () => {
  assert.equal(cfUserStatus.safeParse(fx('cf_status.json')).success, true);
  assert.equal(cfUserStatus.safeParse(fx('cf_bad.json')).success, true);
  assert.equal(acSubmissions.safeParse(fx('ac.json')).success, true);
});

test('syncCf folds the recorded response and is incremental on the second run', async () => {
  const recorded = fx('cf_status.json').result;
  let calls = 0;
  const n = net(async () => { calls++; return resp({ status: 'OK', result: recorded }); });
  const c = newCounters();
  const a = await syncCf(n, c, { problems: {}, highWater: 0 }, 'tourist');
  assert.equal(totalTries(a) > 0, true);
  assert.equal(a.highWater, Math.max(...recorded.map((s) => s.id)));
  const b = await syncCf(n, newCounters(), a, 'tourist');
  assert.deepEqual(b, a);
  assert.equal(c.transport, 'direct');
});

test('verifyCfHandle: canonical handle and the API comment on failure', async () => {
  const n = net(async () => resp({ status: 'OK', result: [{ handle: 'tourist' }] }));
  assert.equal(await verifyCfHandle(n, newCounters(), 'TOURIST'), 'tourist');
  const bad = net(async () => resp(fx('cf_bad.json'), 400));
  await assert.rejects(verifyCfHandle(bad, newCounters(), 'zz'), /not found/);
});

test('syncCf backs off on 429 and gives up after three waits', async () => {
  let calls = 0;
  const n = net(async () => { calls++; return resp({}, 429); });
  await assert.rejects(syncCf(n, newCounters(), { problems: {}, highWater: 0 }, 'h'));
  assert.equal(calls, 4);
});

test('unknown verdicts count as attempts and are reported', async () => {
  const s = (id, v) => ({ id, creationTimeSeconds: id, problem: { contestId: 1, index: 'A' }, verdict: v });
  const n = net(async () => resp({ status: 'OK', result: [s(2, 'SOME_NEW_VERDICT'), s(1, 'OK')] }));
  const c = newCounters();
  const r = await syncCf(n, c, { problems: {}, highWater: 0 }, 'h');
  assert.equal(r.problems['1A'].tries, 2);
  assert.deepEqual([...c.unknownVerdicts], ['SOME_NEW_VERDICT']);
});

test('syncAc with the recorded response: first run stores, second run changes nothing', async () => {
  const rec = fx('ac.json');
  const c0 = clock();
  const n = { gate: makeGate('ac', c0), transport: { fetch: async (u) => { const from = Number(new URL(u).searchParams.get('from_second')); return resp(rec.filter((s) => s.epoch_second >= from)); } }, sleep: c0.sleep };
  const a = await syncAc(n, newCounters(), {}, 'tourist');
  assert.equal(totalTries(a), rec.filter((s) => s.result !== 'CE' && s.result !== 'WJ').length);
  const b = await syncAc(n, newCounters(), a, 'tourist');
  assert.deepEqual(b, a);
});

test('import parsing: LeetCode payload, wrong version, wrong types, oversize, fragment', () => {
  const good = { v: 1, username: 'u', at: 1760000000, method: 'list', statuses: { 'two-sum': 'ac', 'lru-cache': 'notac' } };
  assert.equal(parseImportText(JSON.stringify(good)).kind, 'lc');
  assert.equal(parseImportText(JSON.stringify({ ...good, v: 2 })).kind, 'error');
  assert.equal(parseImportText(JSON.stringify({ ...good, statuses: { x: 'maybe' } })).kind, 'error');
  assert.equal(parseImportText(JSON.stringify({ ...good, at: 'now' })).kind, 'error');
  assert.equal(parseImportText('{not json').kind, 'error');
  assert.equal(parseImportText('[]', MAX_IMPORT_BYTES + 1).kind, 'error');
  assert.equal(parseImportText(JSON.stringify(fx('cf_status.json'))).kind, 'cf');
  assert.equal(parseImportText(JSON.stringify(fx('ac.json'))).kind, 'ac');
  const b64 = Buffer.from(JSON.stringify(good)).toString('base64url');
  assert.equal(decodeLcFragment(`#lc=${b64}`), JSON.stringify(good));
  assert.equal(decodeLcFragment('#other'), null);
});
