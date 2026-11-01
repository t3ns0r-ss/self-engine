#!/usr/bin/env node
// Flags Hinglish (Hindi words in Latin letters) in the prose and code comments of the given lesson files.
// Usage: node scripts/check_english.mjs <file.mdx> ...   (exit 1 if any word is found)
import { readFileSync } from 'node:fs';

const WORDS = new Set(`hai hain nahi nahin kya toh karo karna karke karna kaise kyun kyuki kyunki matlab jaise agar isse yaha yahan wahi wahan
pehle pehla phir wale wala wali mein hoga hogi hota hote dekho dekh sabhi bhi bhai jaata jaate jata jate rakho rakh chahiye sakte sakta sakti lekin
aaya aaye aayega jaldi abhi seedha seedhe sirf bilkul zyada jyada jaada thoda bahut bahar andar upar neeche aage peeche wapas pura poora saare saari
koi kuch kisi aap hum humein mujhe ke ki ka ko aur ya yeh woh wo iska iski uska uski unka isme usme isliye kyunki lagta lagega milega milta karenge
karte karta karti kare kiya kiye gaya gayi gaye hua hui hue banta banti banata chalega chalta dalo daalo nikalo nikaal batao bata likho likha samjho
samajh samjhe dikhta dikhega ho jao jaao jaana jana lo do` .split(/\s+/).filter(Boolean));
// "do", "lo", "ho", "ya" etc. are ambiguous in English; drop the ones that are common English words or identifiers.
for (const w of ['do', 'lo', 'ho', 'ya', 'ke', 'ka', 'ko', 'ki', 'jana', 'jata', 'jate', 'dekh', 'bata', 'hum', 'aap']) WORDS.delete(w);
// ke/ka/ko/ki are the commonest Hinglish words; flag them only when the line has no code characters.
const SOFT = new Set(['ke', 'ka', 'ko', 'ki']);

let bad = 0;
for (const f of process.argv.slice(2)) {
  const lines = readFileSync(f, 'utf8').split('\n');
  let fence = null;
  lines.forEach((line, i) => {
    const m = /^\s*(`{3,}|~{3,})/.exec(line);
    if (m) {
      if (!fence) fence = m[1];
      else if (m[1][0] === fence[0] && m[1].length >= fence.length && /^\s*[`~]+\s*$/.test(line)) fence = null;
      return;
    }
    let text = line;
    if (fence) {
      const c = /(\/\/|#)\s*(.*)$/.exec(line);
      if (!c) return;
      text = c[2];
    } else {
      text = line.replace(/`[^`\n]*`/g, ' ').replace(/\$\$.*?\$\$|\$[^$\n]*\$/g, ' ').replace(/\]\([^)]*\)/g, ']').replace(/https?:\/\/\S+/g, ' ');
    }
    const hits = [];
    for (const w of text.toLowerCase().match(/[a-z]+/g) ?? []) {
      if (WORDS.has(w)) hits.push(w);
      else if (SOFT.has(w) && !/[=;(){}<>\[\]]/.test(text)) hits.push(w);
    }
    if (hits.length) {
      bad++;
      console.log(`${f}:${i + 1}: ${[...new Set(hits)].join(', ')}  | ${line.trim().slice(0, 100)}`);
    }
  });
}
console.log(bad ? `${bad} line(s) with Hinglish words` : 'no Hinglish words found');
process.exit(bad ? 1 : 0);
