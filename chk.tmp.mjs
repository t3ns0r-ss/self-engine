import { loadAll } from './scripts/lib/load.mjs';
import { validateTopics } from './src/lib/validate-topics.mjs';
const d = loadAll(); d.topics['0.1'].draft = false;
console.log(validateTopics(d).filter(e=>e.includes('0-1')).join('\n') || 'no errors');
