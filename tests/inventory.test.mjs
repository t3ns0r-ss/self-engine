import { test } from 'node:test';
import assert from 'node:assert/strict';
import { validateInventory } from '../src/lib/inventory.mjs';

const has = (errs, re) => assert.ok(errs.some((e) => re.test(e)), errs.join('\n') || '(no errors)');
const rows = [
  { track: 'hld', order: 1, id: 'H0.1', kind: 'standard', lab: 'Build a' },
  { track: 'hld', order: 2, id: 'H0.2', kind: 'standard', lab: 'Build b' },
];
const rung = (n, o = {}) => ({ rung: n, card: 'c1', new_force: `force ${n}`, needs_new_structure: n !== 4, tests: 't', ...o });
const topic = (id, o = {}) => ({
  cards: [{ id: 'c1', name: 'C1' }],
  ladder: [rung(1), rung(2), rung(3), rung(4)],
  drill: [1, 2, 3, 4, 5, 6].map((i) => ({ stub: `${id} scenario ${i}`, answer: i < 5 ? { topic: id, card: 'c1' } : 'none' })),
  checkpoint: { title: 'cp', type: 'lab' },
  reviews: [{ set: 1, stubs: [`${id} r1`] }, { set: 2, stubs: [`${id} r2`] }],
  ...o,
});
const inv = () => ({ topics: { 'H0.1': topic('H0.1'), 'H0.2': topic('H0.2', { drill: [1, 2, 3, 4, 5, 6].map((i) => ({ stub: `H0.2 scenario ${i}`, answer: i <= 2 ? 'none' : i < 5 ? { topic: 'H0.1', card: 'c1' } : { topic: 'H0.2', card: 'c1' } })) }) } });

test('a consistent inventory passes', () => assert.deepEqual(validateInventory(inv(), rows), []));
test('every design topic must be listed', () => { const i = inv(); delete i.topics['H0.2']; has(validateInventory(i, rows), /H0\.2 is missing/); });
test('ladder needs a no-new-structure rung, ordered rungs, and cards planned in the same topic', () => {
  let i = inv(); i.topics['H0.1'].ladder[3].needs_new_structure = true; has(validateInventory(i, rows), /needs_new_structure: false/);
  i = inv(); i.topics['H0.1'].ladder[1].card = 'nope'; has(validateInventory(i, rows), /card nope is not planned/);
  i = inv(); i.topics['H0.1'].ladder[1].rung = 5; has(validateInventory(i, rows), /rung 5 is out of order/);
});
test('drill: none quota, earlier-card quota, unknown or later answer cards', () => {
  let i = inv(); i.topics['H0.1'].drill.forEach((d) => (d.answer = { topic: 'H0.1', card: 'c1' })); has(validateInventory(i, rows), /0 "none" drill items of 6/);
  i = inv(); i.topics['H0.2'].drill.forEach((d) => (d.answer = d.answer === 'none' ? d.answer : { topic: 'H0.2', card: 'c1' })); has(validateInventory(i, rows), /0 drill items use an earlier card; at least 1/);
  i = inv(); i.topics['H0.1'].drill[0].answer = { topic: 'H0.2', card: 'c1' }; has(validateInventory(i, rows), /H0\.2\/c1 is not a card of this or an earlier topic/);
});
test('a scenario may not repeat within a track', () => { const i = inv(); i.topics['H0.2'].reviews[0].stubs = ['H0.1 r1']; has(validateInventory(i, rows), /repeats one in H0\.1/); });
