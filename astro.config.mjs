// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import react from '@astrojs/react';
import remarkMath from 'remark-math';
import rehypeKatex from 'rehype-katex';
import { readFileSync, existsSync } from 'node:fs';
import { parse } from 'yaml';

// Sidebar (PLAN.md Section 10.7): Home, Method, Phases 0–7, then the generated pages.
// Each phase lists its intro, every topic in order, and its exam. A topic without a lesson yet
// links to its problem bank page and carries a "soon" badge. data-order lets the browser add
// a "later" badge to topics after the learner's current topic (see src/styles/later-badge.js).
const curriculum = parse(readFileSync('./src/data/curriculum.yaml', 'utf8'));
const PHASES = ['Foundations', 'Array techniques', 'Mathematics I', 'Recursion to dynamic programming', 'Graphs', 'Range data structures', 'Strings', 'Integration'];
const dash = (id) => id.replace('.', '-');
const phaseGroups = PHASES.map((name, phase) => {
  const dir = `./src/content/docs/phase-${phase}`;
  const items = [];
  if (existsSync(`${dir}/index.mdx`)) items.push({ label: 'Introduction', link: `/phase-${phase}/` });
  for (const t of curriculum.filter((x) => x.phase === phase)) {
    const lesson = existsSync(`${dir}/${dash(t.id)}-${t.slug}.mdx`);
    items.push({
      label: `${t.id} ${t.title}`,
      link: lesson ? `/phase-${phase}/${dash(t.id)}-${t.slug}/` : `/bank/${dash(t.id)}/`,
      attrs: { 'data-order': String(t.order), 'data-topic': t.id },
      ...(lesson ? {} : { badge: { text: 'soon', variant: 'note' } }),
    });
  }
  if (existsSync(`${dir}/exam.mdx`)) items.push({ label: 'Phase exam', link: `/phase-${phase}/exam/` });
  return { label: `Phase ${phase}: ${name}`, collapsed: true, items };
});

// SITE_URL comes from .env.deploy at deploy time (PLAN.md Section 14.2); never hard-code a host.
export default defineConfig({
  site: process.env.SITE_URL || undefined,
  markdown: { remarkPlugins: [remarkMath], rehypePlugins: [rehypeKatex] },
  integrations: [
    starlight({
      title: 'CP Training',
      customCss: ['katex/dist/katex.min.css', './src/styles/custom.css'],
      head: [{ tag: 'script', attrs: { src: '/later-badge.js', defer: true } }],
      sidebar: [
        { label: 'Home', link: '/' },
        { label: 'Method', link: '/method/' },
        ...phaseGroups,
        { label: 'Recognition Handbook', link: '/handbook/' },
        { label: 'Glossary', link: '/glossary/' },
        { label: 'Problems', link: '/problems/' },
        { label: 'Problem bank', link: '/bank/' },
        { label: 'Contest log', link: '/contests/' },
        { label: 'Progress', link: '/progress/' },
      ],
    }),
    react(),
  ],
});
