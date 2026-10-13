import test from 'node:test';
import assert from 'node:assert/strict';
import { Gate, GAP_MS, HttpError, withBackoff } from '../src/lib/sync/gate.ts';

function fakeClock() {
  let t = 1_000_000;
  return { now: () => t, sleep: async (ms) => { t += ms; }, advance: (ms) => { t += ms; } };
}

test('gate: requests start at least the gap apart and never overlap', async () => {
  for (const [name, gap] of [['cf', GAP_MS.cf], ['ac', GAP_MS.ac]]) {
    const clock = fakeClock();
    const gate = new Gate(gap, clock);
    const starts = [];
    let inFlight = 0, maxInFlight = 0;
    const job = () => gate.run(async () => {
      starts.push(clock.now());
      inFlight++; maxInFlight = Math.max(maxInFlight, inFlight);
      clock.advance(300); // the request itself takes 300 ms
      await Promise.resolve();
      inFlight--;
    });
    await Promise.all([job(), job(), job(), job()]);
    assert.equal(maxInFlight, 1, name);
    for (let i = 1; i < starts.length; i++) assert.ok(starts[i] - starts[i - 1] >= gap, `${name}: gap ${starts[i] - starts[i - 1]} < ${gap}`);
  }
  assert.ok(GAP_MS.cf >= 2100 && GAP_MS.ac >= 1100);
});

test('gate: a failing job does not block the queue', async () => {
  const clock = fakeClock();
  const gate = new Gate(1000, clock);
  await assert.rejects(gate.run(async () => { throw new Error('x'); }));
  assert.equal(await gate.run(async () => 7), 7);
});

test('withBackoff: 4 s, 8 s, 16 s then stop; non-retryable errors are not retried', async () => {
  const waits = [];
  const sleep = async (ms) => { waits.push(ms); };
  let calls = 0;
  await assert.rejects(withBackoff(async () => { calls++; throw new HttpError(429); }, (e) => e.retryable, sleep));
  assert.equal(calls, 4);
  assert.deepEqual(waits, [4000, 8000, 16000]);
  waits.length = 0; calls = 0;
  const ok = await withBackoff(async () => { if (++calls < 3) throw new HttpError(503); return 'done'; }, (e) => e.retryable, sleep);
  assert.equal(ok, 'done');
  assert.deepEqual(waits, [4000, 8000]);
  calls = 0; waits.length = 0;
  await assert.rejects(withBackoff(async () => { calls++; throw new HttpError(404); }, (e) => e.retryable, sleep));
  assert.equal(calls, 1);
  assert.deepEqual(waits, []);
});
