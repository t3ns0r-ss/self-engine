// Browser tests for profile sync (PROFILE_SYNC_PLAN.md Section 14.2). All platform URLs are intercepted: no real network.
// Run against a built site: BASE=http://localhost:4330 node tests/e2e/sync.cjs
const { chromium } = require(process.env.PLAYWRIGHT_PATH || 'playwright');
const BASE = process.env.BASE || 'http://localhost:4330';
let failures = 0;
const check = (cond, msg) => { console.log(`${cond ? 'ok  ' : 'FAIL'} ${msg}`); if (!cond) failures++; };
const CORS = { 'access-control-allow-origin': '*' };
const now = Math.floor(Date.now() / 1000);
const cfSub = (id, contestId, index, verdict) => ({ id, creationTimeSeconds: now - 1000 + id, problem: { contestId, index, name: 'x' }, verdict });
const CF_RESULT = [cfSub(103, 1354, 'B', 'OK'), cfSub(102, 660, 'C', 'OK'), cfSub(101, 1399, 'A', 'WRONG_ANSWER')];
const json = (body, status = 200) => ({ status, headers: CORS, contentType: 'application/json', body: JSON.stringify(body) });

async function rowStatus(p, id) {
  await p.goto(`${BASE}/problems/`);
  await p.fill('input[aria-label="Search"]', id);
  const row = p.locator('tbody tr', { hasText: id }).first();
  await row.waitFor();
  return { text: await row.locator('td').last().innerText(), cls: (await row.getAttribute('class')) || '' };
}

(async () => {
  const b = await chromium.launch(process.env.CHROMIUM ? { executablePath: process.env.CHROMIUM } : {});
  for (const width of [1200, 375]) {
    console.log(`--- width ${width}`);
    const ctx = await b.newContext({ viewport: { width, height: 900 } });
    const p = await ctx.newPage();
    const errs = [];
    p.on('pageerror', (e) => errs.push(e.message));
    p.on('dialog', (d) => d.accept());

    // 1. Codeforces handle -> statuses appear; a hand-set status stays.
    await p.route('https://codeforces.com/api/user.info*', (r) => r.fulfill(json({ status: 'OK', result: [{ handle: 'Tourist' }] })));
    await p.route('https://codeforces.com/api/user.status*', (r) => r.fulfill(json({ status: 'OK', result: CF_RESULT })));
    await p.goto(`${BASE}/profiles/`);
    await p.evaluate(() => localStorage.setItem('cp:v1:problems', JSON.stringify({ 'cf-660C': { status: 'editorial', hintsOpened: 0 } })));
    await p.fill('#cf-handle', 'tourist');
    await p.click('#cf-h ~ .actions button:has-text("Save and sync")');
    await p.waitForSelector('text=Last sync: just now', { timeout: 5000 });
    check(await p.inputValue('#cf-handle') === 'tourist', 'handle saved');
    check((await p.evaluate(() => JSON.parse(localStorage.getItem('cp:v1:profiles')).codeforces.handle)) === 'Tourist', 'canonical handle stored');
    let s = await rowStatus(p, 'cf-1354B');
    check(/^Solved/.test(s.text) && /CF/.test(s.text) && s.cls.includes('status-solved'), `synced solve shows with CF mark (${JSON.stringify(s.text)})`);
    s = await rowStatus(p, 'cf-660C');
    check(/Read editorial/.test(s.text) && !/CF/.test(s.text), 'hand-set Read editorial is kept and not marked as synced');
    s = await rowStatus(p, 'cf-1399A');
    check(/Attempted/.test(s.text), 'wrong answer shows Attempted');
    const stored = await p.evaluate(() => JSON.parse(localStorage.getItem('cp:v1:problems')));
    check(JSON.stringify(stored) === JSON.stringify({ 'cf-660C': { status: 'editorial', hintsOpened: 0 } }), 'sync never wrote into the learner log');

    // Sync now gives visible feedback (the button reports what happened).
    await p.goto(`${BASE}/profiles/`);
    await p.click('#cf-h ~ .actions button:has-text("Sync now")');
    await p.waitForSelector('#cf-h ~ p[role=status]:has-text("Synced:")', { timeout: 10000 });
    check(true, 'Sync now reports its result on the Profiles page');
    await p.goto(`${BASE}/`);
    await p.waitForSelector('.dashboard button:has-text("Sync now")');
    await p.click('.dashboard button:has-text("Sync now")');
    await p.waitForSelector('.dashboard [role=status]:has-text("Synced:")', { timeout: 10000 });
    check(true, 'Sync now reports its result on the dashboard');

    // 7. Remove the handle: synced statuses go, hand-set stays.
    await p.goto(`${BASE}/profiles/`);
    await p.click('#cf-h ~ .actions button:has-text("Remove")');
    await p.waitForSelector('text=Removed.');
    s = await rowStatus(p, 'cf-1354B');
    check(/Not started|—/.test(s.text), 'synced status disappears after removing the handle');
    s = await rowStatus(p, 'cf-660C');
    check(/Read editorial/.test(s.text), 'hand-set status remains after removing the handle');

    // 2. Direct fetch blocked -> JSONP.
    await p.unroute('https://codeforces.com/api/user.status*');
    await p.unroute('https://codeforces.com/api/user.info*');
    await p.route('https://codeforces.com/api/**', (r) => {
      const u = new URL(r.request().url());
      const cb = u.searchParams.get('jsonp');
      if (!cb) return r.abort('failed');
      const body = u.pathname.endsWith('user.info') ? { status: 'OK', result: [{ handle: 'tourist' }] } : { status: 'OK', result: CF_RESULT };
      return r.fulfill({ status: 200, contentType: 'application/javascript', body: `${cb}(${JSON.stringify(body)})` });
    });
    await p.goto(`${BASE}/profiles/`);
    await p.fill('#cf-handle', 'tourist');
    await p.click('#cf-h ~ .actions button:has-text("Save and sync")');
    await p.waitForSelector('text=Last sync: just now', { timeout: 8000 });
    await p.waitForSelector('text=via JSONP');
    s = await rowStatus(p, 'cf-1354B');
    check(/^Solved/.test(s.text), 'statuses appear through the JSONP route');
    check((await p.evaluate(() => Object.keys(window).filter((k) => k.startsWith('__cpJsonp')).length)) === 0, 'JSONP callbacks are cleaned up');

    // 3. AtCoder: 1200 submissions over three pages; a second sync makes one request.
    const all = [];
    for (let i = 1; i <= 1200; i++) all.push({ id: i, epoch_second: 1000 + i, problem_id: i % 2 ? 'abc326_c' : 'abc229_d', contest_id: 'x', result: i === 1200 ? 'AC' : 'WA' });
    let acRequests = 0;
    await p.route('https://kenkoooo.com/**', (r) => {
      acRequests++;
      const from = Number(new URL(r.request().url()).searchParams.get('from_second'));
      return r.fulfill(json(all.filter((x) => x.epoch_second >= from).slice(0, 500)));
    });
    await p.goto(`${BASE}/profiles/`);
    await p.fill('#ac-user', 'tourist');
    await p.click('#ac-h ~ .actions button:has-text("Save and sync")');
    await p.waitForFunction(() => document.body.innerText.includes('Saved and synced'), null, { timeout: 15000 });
    check(acRequests === 3, `three AtCoder requests for 1200 submissions (${acRequests})`);
    const tries = await p.evaluate(() => Object.values(JSON.parse(localStorage.getItem('cp:v1:sync:ac')).problems).reduce((n, e) => n + e.tries, 0));
    check(tries === 1200, `all 1200 submissions counted once (${tries})`);
    acRequests = 0;
    const runsBefore = await p.evaluate(() => JSON.parse(localStorage.getItem('cp:v1:sync:log')).length);
    await p.click('#ac-h ~ .actions button:has-text("Sync now")');
    await p.waitForFunction((n) => JSON.parse(localStorage.getItem('cp:v1:sync:log')).length > n, runsBefore, { timeout: 10000 });
    check(acRequests === 1, `second sync makes one request (${acRequests})`);
    const tries2 = await p.evaluate(() => Object.values(JSON.parse(localStorage.getItem('cp:v1:sync:ac')).problems).reduce((n, e) => n + e.tries, 0));
    check(tries2 === 1200, 'second sync changes nothing');
    s = await rowStatus(p, 'ac-abc229_d');
    check(/^Solved/.test(s.text) && /AC/.test(s.text), 'AtCoder accepted submission shows as Solved');

    // 4. LeetCode import through #lc= ; the fragment is removed.
    const payload = { v: 1, username: 'me', at: now, method: 'list', statuses: { 'longest-substring-without-repeating-characters': 'ac', 'subarray-product-less-than-k': 'notac' } };
    const frag = Buffer.from(JSON.stringify(payload)).toString('base64url');
    await p.goto(`${BASE}/profiles/#lc=${frag}`);
    await p.waitForSelector('text=Imported 2 LeetCode problems');
    check(!(await p.evaluate(() => location.hash)), 'the #lc= fragment is removed from the address bar');
    s = await rowStatus(p, 'lc-longest-substring-without-repeating-characters');
    check(/^Solved/.test(s.text) && /LC/.test(s.text), 'LeetCode import shows Solved');
    s = await rowStatus(p, 'lc-subarray-product-less-than-k');
    check(/Attempted/.test(s.text), 'LeetCode notac shows Attempted');

    // The snippet button fills in the username and site address.
    await p.goto(`${BASE}/profiles/`);
    await p.fill('#lc-user', 'me');
    await p.click('button:has-text("Copy LeetCode snippet")');
    await p.click('summary:has-text("Show the snippet")');
    const snippetText = await p.locator('details pre code').innerText();
    check(snippetText.includes('const USERNAME = "me";') && snippetText.includes(`${BASE}/profiles/`) && snippetText.split('\n').length <= 80, 'LeetCode snippet is generated for this user and site');

    // Export keeps profiles and the LeetCode cache, drops the rebuildable caches.
    await p.goto(`${BASE}/progress/`);
    const exported = await p.evaluate(() => { const o = {}; for (const k of ['cp:v1:profiles','cp:v1:sync:lc','cp:v1:sync:cf','cp:v1:sync:ac']) o[k] = localStorage.getItem(k) !== null; return o; });
    check(exported['cp:v1:profiles'] && exported['cp:v1:sync:lc'], 'profiles and LeetCode cache stored');

    check(errs.length === 0, `no page errors ${errs.join(' | ')}`);
    if (width === 375) check(await p.evaluate(() => document.documentElement.scrollWidth <= window.innerWidth + 1), 'no horizontal scroll at 375 px');
    await ctx.close();
  }

  // 5 and 6. Checkpoint of topic 1.3: timer window verification, and a problem solved before it was assigned.
  const CP = `${BASE}/phase-1/1-3-two-pointers/`;
  async function linkAndOpen(ctx, resultFor) {
    const p = await ctx.newPage();
    p.on('dialog', (d) => d.accept());
    await p.route('https://codeforces.com/api/user.info*', (r) => r.fulfill(json({ status: 'OK', result: [{ handle: 'tourist' }] })));
    await p.route('https://codeforces.com/api/user.status*', (r) => r.fulfill(json({ status: 'OK', result: resultFor() })));
    await p.goto(`${BASE}/profiles/`);
    await p.fill('#cf-handle', 'tourist');
    await p.click('#cf-h ~ .actions button:has-text("Save and sync")');
    await p.waitForSelector('text=Last sync: just now', { timeout: 8000 });
    await p.goto(CP);
    return p;
  }
  {
    const ctx = await b.newContext({ viewport: { width: 1200, height: 900 } });
    let accepted = false;
    const p = await linkAndOpen(ctx, () => (accepted ? [cfSub(300, 6, 'C', 'OK')].map((x) => ({ ...x, creationTimeSeconds: Math.floor(Date.now() / 1000) })) : []));
    await p.locator('button:has-text("Start the 90-minute checkpoint")').click();
    await p.waitForSelector('.timer');
    accepted = true; // accepted inside the window
    await p.locator('button:has-text("I\'m done early")').click();
    await p.waitForSelector('text=verified on Codeforces', { timeout: 15000 });
    const boxes = p.locator('.checkpoint input[type=checkbox]');
    check(await boxes.count() === 3 && await boxes.nth(2).isChecked(), '5: accepted submission inside the window ticks the box, marked verified');
    check(!(await boxes.nth(0).isChecked()) && (await p.locator('text=confirm by hand').count()) === 2, '5: LeetCode problems are left for the learner to confirm');
    await boxes.nth(2).uncheck();
    check(await p.locator('text=confirmed by you').count() === 1, '5: an override shows "confirmed by you"');
    await ctx.close();
  }
  {
    const ctx = await b.newContext({ viewport: { width: 1200, height: 900 } });
    // cf-6C was accepted long before the checkpoint was assigned.
    const p = await linkAndOpen(ctx, () => [{ ...cfSub(400, 6, 'C', 'OK'), creationTimeSeconds: now - 86400 * 30 }]);
    await p.locator('button:has-text("Start the 90-minute checkpoint")').click();
    await p.waitForSelector('.timer');
    check(await p.locator('text=You solved this before it was assigned').count() === 1, '6: compromised problem shows the note');
    await p.locator('button:has-text("I\'m done early")').click();
    await p.waitForSelector('text=Time is up');
    const disabled = await p.locator('.checkpoint input[type=checkbox]').nth(2).isDisabled();
    check(disabled, '6: a compromised problem cannot be ticked, it does not count');
    await p.locator('button:has-text("Submit results")').click();
    const topicState = await p.evaluate(() => JSON.parse(localStorage.getItem('cp:v1:topics'))['1.3']);
    check(JSON.stringify(topicState.checkpointCompromised) === JSON.stringify(['cf-6C']), '6: the compromised problem is recorded');
    const shown = await p.evaluate(() => Object.keys(JSON.parse(localStorage.getItem('cp:v1:shown'))));
    check(shown.includes('cf-6C') && shown.length >= 3, '6: shown times are recorded when the checkpoint starts');
    await p.goto(`${BASE}/progress/`);
    await p.click('button:has-text("Copy feedback")');
    await p.waitForSelector('summary:has-text("Contains names of reserved problems")');
    check(await p.locator('details[open]').count() === 0, '6: the spoilers section is collapsed by default');
    await ctx.close();
  }
  await b.close();
  console.log(failures ? `${failures} FAILED` : 'sync e2e passed');
  process.exit(failures ? 1 : 0);
})();
