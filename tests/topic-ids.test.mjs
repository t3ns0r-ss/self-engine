// The topic ids follow the reading order, and learner data saved under the old ids is moved to the new ids once.
import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { parse } from 'yaml';
import { OLD_TO_NEW, ID_SCHEME, migrateProgress, renumberCardValue, renumberTopicId } from '../src/lib/topicIds.ts';

const curriculum = parse(readFileSync('src/data/curriculum.yaml', 'utf8')).filter((r) => r.track === 'cp');

test('CP topic ids ascend with the reading order inside every phase', () => {
  for (let ph = 0; ph <= 7; ph++) {
    const rows = curriculum.filter((r) => r.phase === ph).sort((a, b) => a.order - b.order);
    rows.forEach((r, i) => {
      assert.match(r.id, new RegExp(`^${ph}\\.\\d+$`), r.id);
      if (i > 0) assert.ok(Number(r.id.split('.')[1]) > Number(rows[i - 1].id.split('.')[1]), `${r.id} comes after ${rows[i - 1].id} in reading order but has a smaller number`);
    });
  }
});

test('the old-to-new map is one-to-one and every new id exists now', () => {
  const ids = new Set(curriculum.map((r) => r.id));
  const values = Object.values(OLD_TO_NEW);
  assert.equal(new Set(values).size, values.length);
  for (const v of values) assert.ok(ids.has(v), v);
  // an old id that is not a topic now (4.9) is retired: nothing is stored under it any more
  assert.deepEqual(Object.keys(OLD_TO_NEW).filter((k) => !ids.has(k)), ['4.9']);
  for (const [k, v] of Object.entries(OLD_TO_NEW)) assert.notEqual(k, v);
  assert.equal(renumberTopicId('1.3'), '1.3');
  assert.equal(renumberTopicId('7.10'), '7.2');
  assert.equal(renumberTopicId('7.8'), '7.10');
});

const old = {
  topics: { '3.2': { started: '2026-10-01' }, '3.9': { checkpointPassedOn: '2026-11-01' }, '1.3': { started: '2026-09-01' }, '7.10': { started: 'x' } },
  drills: { 'cf-1A': { chosenCard: '2.3:ncr-mod-p', revealed: true }, 'cf-2B': { chosenCard: '1.3:shrinkable-window' }, 'cf-3C': { chosenCard: '' }, 'cf-4D': { revealed: false } },
  settings: { currentTopic: '4.7', other: 1 },
};

test('migrateProgress moves topic keys, drill answers and the current topic once', () => {
  const m = migrateProgress(old);
  assert.deepEqual(Object.keys(m.topics).sort(), ['1.3', '3.2', '3.3', '7.2']);
  assert.equal(m.topics['3.3'].started, '2026-10-01');
  assert.equal(m.topics['3.2'].checkpointPassedOn, '2026-11-01');
  assert.equal(m.topics['7.2'].started, 'x');
  assert.equal(m.drills['cf-1A'].chosenCard, '2.5:ncr-mod-p');
  assert.equal(m.drills['cf-1A'].revealed, true);
  assert.equal(m.drills['cf-2B'].chosenCard, '1.3:shrinkable-window');
  assert.equal(m.drills['cf-3C'].chosenCard, '');
  assert.deepEqual(m.drills['cf-4D'], { revealed: false });
  assert.deepEqual(m.settings, { currentTopic: '4.8', other: 1, idScheme: ID_SCHEME });
  assert.equal(old.topics['3.2'].started, '2026-10-01', 'the input is not modified');
});

test('the current topic can also be stored per track', () => {
  const m = migrateProgress({ settings: { currentTopic: { cp: '7.8', lld: 'L2.1' } } });
  assert.deepEqual(m.settings.currentTopic, { cp: '7.10', lld: 'L2.1' });
  assert.equal(migrateProgress({}).settings.idScheme, ID_SCHEME);
  assert.equal(migrateProgress({ topics: null, drills: null, settings: null }).topics, null);
});

test('card values of the design tracks and unknown shapes are left alone', () => {
  assert.equal(renumberCardValue('L2.1/strategy'), 'L2.1/strategy');
  assert.equal(renumberCardValue('none'), 'none');
  assert.equal(renumberCardValue(5), 5);
  assert.equal(renumberCardValue('3.4:knapsack-unbounded'), '3.5:knapsack-unbounded');
});

// ---- storage.ts with a fake localStorage ----
function fakeStorage(initial = {}) {
  const m = new Map(Object.entries(initial).map(([k, v]) => [k, JSON.stringify(v)]));
  return {
    m,
    getItem: (k) => (m.has(k) ? m.get(k) : null),
    setItem: (k, v) => { m.set(k, String(v)); },
    removeItem: (k) => { m.delete(k); },
  };
}
let n = 0;
const freshStorage = async (ls) => {
  globalThis.localStorage = ls;
  return import(`../src/lib/storage.ts?case=${++n}`);
};
const stored = (ls, k) => JSON.parse(ls.getItem(k));

test('the first read moves old data, a second read does not move it again', async () => {
  const ls = fakeStorage({ 'cp:v1:topics': old.topics, 'cp:v1:drills': old.drills, 'cp:v1:settings': old.settings });
  const s = await freshStorage(ls);
  assert.deepEqual(Object.keys(s.getTopics()).sort(), ['1.3', '3.2', '3.3', '7.2']);
  assert.equal(s.getCurrentTopic(), '4.8');
  assert.equal(s.getDrills()['cf-1A'].chosenCard, '2.5:ncr-mod-p');
  assert.equal(stored(ls, 'cp:v1:settings').idScheme, ID_SCHEME);
  // a new page load (new module instance) on already migrated data changes nothing
  const before = JSON.stringify([...ls.m]);
  const s2 = await freshStorage(ls);
  assert.deepEqual(Object.keys(s2.getTopics()).sort(), ['1.3', '3.2', '3.3', '7.2']);
  assert.equal(s2.getCurrentTopic(), '4.8');
  assert.equal(JSON.stringify([...ls.m]), before);
});

test('a learner with no data only gets the mark; later writes use the new ids', async () => {
  const ls = fakeStorage();
  const s = await freshStorage(ls);
  assert.deepEqual(s.getTopics(), {});
  assert.equal(stored(ls, 'cp:v1:settings').idScheme, ID_SCHEME);
  assert.equal(ls.getItem('cp:v1:topics'), null);
  s.saveTopic('7.2', { started: 'd' });
  const s2 = await freshStorage(ls);
  assert.deepEqual(Object.keys(s2.getTopics()), ['7.2']);
});

test('exports carry the mark; an old export is moved when it is imported', async () => {
  const ls = fakeStorage({ 'cp:v1:topics': old.topics, 'cp:v1:drills': old.drills, 'cp:v1:settings': old.settings, 'cp:v1:problems': {} });
  const s = await freshStorage(ls);
  const exp = s.exportAll();
  assert.equal(exp['cp:v1:settings'].idScheme, ID_SCHEME);
  assert.deepEqual(Object.keys(exp['cp:v1:topics']).sort(), ['1.3', '3.2', '3.3', '7.2']);

  const legacy = { format: 'cp-training-progress', version: 1, exportedOn: '2026-11-01', 'cp:v1:problems': {}, 'cp:v1:topics': old.topics, 'cp:v1:drills': old.drills, 'cp:v1:settings': old.settings, 'cp:v1:contests': null };
  const ls2 = fakeStorage();
  const s2 = await freshStorage(ls2);
  assert.equal(s2.importAll(legacy), null);
  assert.deepEqual(Object.keys(s2.getTopics()).sort(), ['1.3', '3.2', '3.3', '7.2']);
  assert.equal(s2.getCurrentTopic(), '4.8');
  // importing the new export again must not move ids a second time
  assert.equal(s2.importAll(s2.exportAll()), null);
  assert.deepEqual(Object.keys(s2.getTopics()).sort(), ['1.3', '3.2', '3.3', '7.2']);
  // an old export without settings at all
  assert.equal(s2.importAll({ format: 'cp-training-progress', 'cp:v1:problems': {}, 'cp:v1:topics': { '3.9': {} }, 'cp:v1:drills': {}, 'cp:v1:settings': null, 'cp:v1:contests': null }), null);
  assert.deepEqual(Object.keys(s2.getTopics()), ['3.2']);
});

test('a failed write rolls back, so the next load can try again', async () => {
  const ls = fakeStorage({ 'cp:v1:topics': old.topics, 'cp:v1:drills': old.drills, 'cp:v1:settings': old.settings });
  const realSet = ls.setItem;
  ls.setItem = (k, v) => { if (k === 'cp:v1:drills') throw new Error('quota'); realSet(k, v); };
  const s = await freshStorage(ls);
  s.getTopics();
  assert.deepEqual(stored(ls, 'cp:v1:topics'), old.topics);
  assert.deepEqual(stored(ls, 'cp:v1:settings'), old.settings);
  ls.setItem = realSet;
  const s2 = await freshStorage(ls);
  assert.deepEqual(Object.keys(s2.getTopics()).sort(), ['1.3', '3.2', '3.3', '7.2']);
});

test.after(() => { delete globalThis.localStorage; });
