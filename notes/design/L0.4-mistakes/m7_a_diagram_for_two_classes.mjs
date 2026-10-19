// A diagram for a two-class design: how much does it say that one sentence does not?
import fs from 'node:fs';
const root = process.env.ROOT;
const src = fs.readFileSync(`${root}/code/L0.3/owned-engine/parts.hpp`, 'utf8');
const nonBlank = (s) => s.split('\n').filter((l) => l.trim() && !l.trim().startsWith('//')).length;
const diagram = 'classDiagram\n  Car *-- Engine\n';
const sentence = 'A Car owns its Engine, which is built with the car and destroyed with it.';
console.log(`header: ${nonBlank(src)} lines`);
console.log(`diagram: ${nonBlank(diagram)} lines, and it still needs the sentence to say what the diamond means`);
console.log(`sentence: ${sentence.split(/\s+/).length} words, and it says everything the diagram says`);
