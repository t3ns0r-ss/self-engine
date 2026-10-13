import test from 'node:test';
import assert from 'node:assert/strict';
import { getJson, scriptJsonp, directUrl, proxyUrl, TransportError } from '../src/lib/sync/transport.ts';
import { HttpError } from '../src/lib/sync/gate.ts';

const req = { platform: 'cf', method: 'user.status', params: { handle: 'tourist', from: 1, count: 2 } };
const ok = (body, status = 200) => ({ ok: status < 400, status, json: async () => body });

test('URLs: direct and proxy', () => {
  assert.equal(directUrl(req), 'https://codeforces.com/api/user.status?handle=tourist&from=1&count=2');
  assert.equal(directUrl({ platform: 'ac', method: '', params: { user: 'u', from_second: 5 } }), 'https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions?user=u&from_second=5');
  assert.equal(proxyUrl(req, '/sync-proxy/'), '/sync-proxy/cf/api/user.status?handle=tourist&from=1&count=2');
});

test('direct success; a FAILED body on HTTP 400 is a real answer, not a transport failure', async () => {
  let r = await getJson(req, { fetch: async () => ok({ status: 'OK', result: [] }) });
  assert.equal(r.transport, 'direct');
  r = await getJson(req, { fetch: async () => ok({ status: 'FAILED', comment: 'nope' }, 400) });
  assert.equal(r.data.status, 'FAILED');
});

test('chain: TypeError -> JSONP (Codeforces) -> proxy; preferred transport goes first', async () => {
  const calls = [];
  const fetchFn = async (u) => { calls.push(u); if (u.startsWith('http')) throw new TypeError('blocked'); return ok({ status: 'OK', via: 'proxy' }); };
  const jsonpFail = async () => { calls.push('jsonp'); throw new TypeError('x'); };
  let r = await getJson(req, { fetch: fetchFn, loadJsonp: jsonpFail, proxyBase: '/p' });
  assert.equal(r.transport, 'proxy');
  assert.deepEqual(calls.map((c) => (c.startsWith('http') ? 'direct' : c.startsWith('/p') ? 'proxy' : c)), ['direct', 'jsonp', 'proxy']);
  calls.length = 0;
  r = await getJson(req, { fetch: fetchFn, loadJsonp: jsonpFail, proxyBase: '/p', preferred: 'proxy' });
  assert.equal(calls[0].startsWith('/p'), true);
  calls.length = 0;
  r = await getJson(req, { fetch: fetchFn, loadJsonp: async (u) => { calls.push('jsonp'); return { status: 'OK' }; } });
  assert.equal(r.transport, 'jsonp');
});

test('AtCoder never uses JSONP; all routes failing gives TransportError; 429 is thrown as HttpError', async () => {
  const ac = { platform: 'ac', method: '', params: { user: 'u', from_second: 0 } };
  await assert.rejects(getJson(ac, { fetch: async () => { throw new TypeError('b'); }, loadJsonp: async () => { throw new Error('should not run'); } }), TransportError);
  await assert.rejects(getJson(req, { fetch: async () => ok({}, 429), loadJsonp: async () => { throw new Error('no'); } }), (e) => e instanceof HttpError && e.retryable);
});

function fakeDom() {
  const head = { children: [], appendChild(s) { this.children.push(s); } };
  const doc = { head, createElement: () => ({ removed: false, remove() { this.removed = true; } }) };
  return { doc, win: {}, head };
}

test('JSONP removes its script element and callback after success, failure and timeout', async () => {
  // success
  let d = fakeDom();
  let p = scriptJsonp('https://x/api?a=1', 1000, d.doc, d.win);
  let script = d.head.children[0];
  const name = /jsonp=(\w+)/.exec(script.src)[1];
  d.win[name]({ status: 'OK' });
  assert.deepEqual(await p, { status: 'OK' });
  assert.equal(script.removed, true);
  assert.equal(name in d.win, false);
  // failure
  d = fakeDom();
  p = scriptJsonp('https://x/api?a=1', 1000, d.doc, d.win);
  script = d.head.children[0];
  script.onerror();
  await assert.rejects(p, TypeError);
  assert.equal(script.removed, true);
  assert.equal(Object.keys(d.win).length, 0);
  // timeout
  d = fakeDom();
  p = scriptJsonp('https://x/api?a=1', 10, d.doc, d.win);
  script = d.head.children[0];
  await assert.rejects(p, TypeError);
  assert.equal(script.removed, true);
  assert.equal(Object.keys(d.win).length, 0);
});
