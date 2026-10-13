import test from 'node:test';
import assert from 'node:assert/strict';
import vm from 'node:vm';
import { leetCodeSnippet } from '../src/lib/sync/snippet.ts';
import { decodeLcFragment, parseImportText } from '../src/lib/sync/leetcode.ts';

const SITE = 'https://example.com/self-engine/profiles/';

test('snippet is short, readable and fills in the site and username safely', () => {
  const s = leetCodeSnippet(SITE, ' me"; alert(1); // ');
  assert.ok(s.split('\n').length <= 80, `${s.split('\n').length} lines`);
  assert.ok(s.includes(JSON.stringify(SITE)));
  assert.ok(s.includes(JSON.stringify('me"; alert(1); //')));
  assert.doesNotThrow(() => new vm.Script(s));
});

// Runs the snippet against a stub of leetcode.com and returns what it logged.
async function run({ pages, hostname = 'leetcode.com', ok = true, shape = true }) {
  const logs = [];
  const calls = [];
  let copied = null;
  const ctx = {
    location: { hostname },
    document: { cookie: 'csrftoken=abc; LEETCODE_SESSION=SECRET' },
    console: { log: (...a) => logs.push(a.join(' ')) },
    setTimeout: (f) => { f(); return 0; }, // skip the 1.1 s waits
    btoa: (x) => Buffer.from(x, 'binary').toString('base64'),
    copy: (x) => { copied = x; },
    fetch: async (url, init) => {
      const v = JSON.parse(init.body).variables;
      calls.push({ url, headers: init.headers, v });
      const all = pages[v.filters.status] || [];
      return { ok, json: async () => (shape ? { data: { problemsetQuestionList: { total: all.length, questions: all.slice(v.skip, v.skip + v.limit) } } } : { nope: 1 }) };
    },
  };
  ctx.globalThis = ctx;
  await vm.runInNewContext(leetCodeSnippet(SITE, 'me'), ctx);
  return { logs, calls, copied };
}
const slugs = (n, p) => Array.from({ length: n }, (_, i) => ({ titleSlug: `${p}-${i}`, status: 'x' }));

test('snippet pages through AC and TRIED, sends only csrftoken, and produces an importable result', async () => {
  const r = await run({ pages: { AC: slugs(120, 'solved'), TRIED: slugs(3, 'tried') } });
  assert.equal(r.calls.length, 3 + 1, 'AC 120 -> 3 pages, TRIED 3 -> 1 page');
  assert.ok(r.calls.every((c) => c.url === '/graphql' && c.headers['x-csrftoken'] === 'abc'));
  assert.ok(!JSON.stringify(r.logs).includes('SECRET'), 'never prints the session cookie');
  const link = r.logs.find((l) => l.startsWith(SITE + '#lc='));
  const parsed = parseImportText(decodeLcFragment(link.slice(SITE.length)));
  assert.equal(parsed.kind, 'lc');
  assert.equal(Object.keys(parsed.payload.statuses).length, 123);
  assert.equal(parsed.payload.statuses['solved-5'], 'ac');
  assert.equal(parsed.payload.statuses['tried-1'], 'notac');
  assert.deepEqual(parseImportText(r.copied).payload, parsed.payload);
});

test('snippet: AC wins over TRIED; nothing found, wrong site and changed schema stop with a plain message', async () => {
  const both = await run({ pages: { AC: [{ titleSlug: 'x', status: 'ac' }], TRIED: [{ titleSlug: 'x', status: 'notac' }] } });
  assert.equal(parseImportText(both.copied).payload.statuses.x, 'ac');
  const none = await run({ pages: {} });
  assert.match(none.logs.join('\n'), /logged in/);
  assert.equal(none.copied, null);
  const wrong = await run({ pages: {}, hostname: 'example.org' });
  assert.equal(wrong.calls.length, 0);
  assert.match(wrong.logs.join('\n'), /Open https:\/\/leetcode\.com/);
  const changed = await run({ pages: { AC: slugs(1, 'a') }, shape: false });
  assert.match(changed.logs.join('\n'), /LeetCode changed; ask for an update/);
  assert.equal(changed.calls.length, 1, 'does not retry in a loop');
});
