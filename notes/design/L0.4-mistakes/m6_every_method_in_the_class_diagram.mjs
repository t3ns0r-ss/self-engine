// A class diagram that lists every method and field next to the classes: how long is it compared with the structure alone?
import fs from 'node:fs';
const root = process.env.ROOT;
const src = fs.readFileSync(`${root}/code/L0.4/shop-model/shop.hpp`, 'utf8');
const diagram = fs.readFileSync(`${root}/code/L0.4/shop-model/diagram.mmd`, 'utf8');
const nonBlank = (s) => s.split('\n').filter((l) => l.trim() && !l.trim().startsWith('//')).length;
const methods = (src.match(/^ {4}(?!if|for|return|throw)\S[^\n]*\)[^;{\n]*(\{.*|;)$/gm) ?? []).length;
const members = (src.match(/^ {4}[\w:<>*&, ]+\s+\w+_;$/gm) ?? []).length;
const classes = (src.match(/^class \w+/gm) ?? []).length;
console.log(`classes: ${classes}`);
console.log(`structure only (arrows between classes): ${nonBlank(diagram)} lines`);
console.log(`with every method and member listed: ${nonBlank(diagram) + methods + members} lines (${methods} methods, ${members} members)`);
console.log(`the header itself: ${nonBlank(src)} lines`);
