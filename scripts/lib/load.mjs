// Loads and schema-checks curriculum, pattern files, bank files, and bank notes from disk.
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { parse } from 'yaml';
import { curriculumFile, patternFile, bankFile, topicFile, glossaryFile } from '../../src/lib/schemas.mjs';
import { findLessons } from '../../src/lib/lessons.mjs';

export const ROOT = join(dirname(fileURLToPath(import.meta.url)), '..', '..');
const DATA = join(ROOT, 'src', 'data');

function parseWith(schema, path, errors) {
  let raw;
  try {
    raw = parse(readFileSync(path, 'utf8'));
  } catch (e) {
    errors.push(`${path.slice(ROOT.length + 1)}: YAML error: ${e.message}`);
    return null;
  }
  const r = schema.safeParse(raw);
  if (!r.success) {
    for (const issue of r.error.issues)
      errors.push(`${path.slice(ROOT.length + 1)}: ${issue.path.join('.') || '(root)'}: ${issue.message}`);
    return null;
  }
  return r.data;
}

const yamlFiles = (dir) => (existsSync(dir) ? readdirSync(dir).filter((f) => f.endsWith('.yaml')).sort() : []);

/** @returns {{curriculum, patterns, banks, notes, topics, glossary, lessons, errors: string[]}} */
export function loadAll() {
  const errors = [];
  const curriculum = parseWith(curriculumFile, join(DATA, 'curriculum.yaml'), errors) ?? [];
  const patterns = {};
  for (const f of yamlFiles(join(DATA, 'bank', 'patterns'))) {
    const d = parseWith(patternFile, join(DATA, 'bank', 'patterns', f), errors);
    if (d) {
      if (f !== `${d.topic.replace('.', '-')}.yaml`) errors.push(`src/data/bank/patterns/${f}: file name does not match topic ${d.topic}`);
      patterns[d.topic] = d;
    }
  }
  const banks = {};
  const notes = {};
  for (const f of yamlFiles(join(DATA, 'bank'))) {
    const d = parseWith(bankFile, join(DATA, 'bank', f), errors);
    if (d) {
      if (f !== `${d.topic.replace('.', '-')}.yaml`) errors.push(`src/data/bank/${f}: file name does not match topic ${d.topic}`);
      banks[d.topic] = d;
      const notePath = join(ROOT, 'notes', 'bank', `${d.topic}.md`);
      notes[d.topic] = existsSync(notePath) ? readFileSync(notePath, 'utf8') : null;
    }
  }
  const topics = {};
  for (const f of yamlFiles(join(DATA, 'topics'))) {
    const d = parseWith(topicFile, join(DATA, 'topics', f), errors);
    if (d) {
      if (f !== `${d.id.replace('.', '-')}.yaml`) errors.push(`src/data/topics/${f}: file name does not match topic ${d.id}`);
      topics[d.id] = d;
    }
  }
  const glossaryPath = join(DATA, 'glossary.yaml');
  const glossary = existsSync(glossaryPath) ? parseWith(glossaryFile, glossaryPath, errors) ?? [] : [];
  const { lessons, errors: lessonErrors } = findLessons(ROOT);
  errors.push(...lessonErrors);
  return { curriculum, patterns, banks, notes, topics, glossary, lessons, errors };
}
