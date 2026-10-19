// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import react from '@astrojs/react';
import remarkMath from 'remark-math';
import rehypeKatex from 'rehype-katex';
import rehypeMermaid from 'rehype-mermaid';
import { readFileSync, existsSync } from 'node:fs';
import { parse } from 'yaml';

// Sidebar (PLAN.md Section 10.7): Home, Method, Phases 0–7, then the generated pages.
// Each phase lists its intro, every topic in order, and its exam. A topic without a lesson yet
// links to its problem bank page and carries a "soon" badge. data-order lets the browser add
// a "later" badge to topics after the learner's current topic (see src/styles/later-badge.js).
const allRows = parse(readFileSync('./src/data/curriculum.yaml', 'utf8'));
const curriculum = allRows.filter((x) => x.track === 'cp');
// GitHub Pages serves the site under /<repo>/; BASE_PATH is set by the Pages workflow.
const base = process.env.BASE_PATH || '/';
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
      // 7.8 has no practice set, so before its lesson exists it points at the bank overview.
      link: lesson ? `/phase-${phase}/${dash(t.id)}-${t.slug}/` : t.id === '7.8' ? '/bank/' : `/bank/${dash(t.id)}/`,
      attrs: { 'data-order': String(t.order), 'data-topic': t.id },
      ...(lesson ? {} : { badge: { text: 'soon', variant: 'note' } }),
    });
  }
  if (existsSync(`${dir}/exam.mdx`)) items.push({ label: 'Phase exam', link: `/phase-${phase}/exam/` });
  return { label: `Phase ${phase}: ${name}`, collapsed: true, items };
});

// LLD and HLD groups (DESIGN_TRACKS_PLAN.md Section 11.1): per phase an intro, the lessons, and an exam; topics without a
// lesson yet link to the track handbook with a "soon" badge.
const designPhases = (track, names) => Object.entries(names).map(([ph, name]) => {
  const n = ph.slice(1);
  const dir = `./src/content/docs/${track}/phase-${n}`;
  const items = [];
  if (existsSync(`${dir}/index.mdx`)) items.push({ label: 'Introduction', link: `/${track}/phase-${n}/` });
  for (const t of allRows.filter((x) => x.track === track && x.phase === ph)) {
    const lesson = existsSync(`${dir}/${dash(t.id)}-${t.slug}.mdx`);
    items.push({
      label: `${t.id} ${t.title.length > 60 ? t.title.slice(0, 57) + '…' : t.title}`,
      link: lesson ? `/${track}/phase-${n}/${dash(t.id).toLowerCase()}-${t.slug}/` : `/${track}/handbook/`,
      attrs: { 'data-order': String(t.order), 'data-topic': t.id },
      ...(lesson ? {} : { badge: { text: 'soon', variant: 'note' } }),
    });
  }
  if (existsSync(`${dir}/exam.mdx`)) items.push({ label: 'Phase exam', link: `/${track}/phase-${n}/exam/` });
  return { label: `Phase ${ph}: ${name}`, collapsed: true, items };
});
const phaseNames = (track) => Object.fromEntries([...readFileSync('./src/lib/design-phases.ts', 'utf8').matchAll(/^\s+([LH]\d): "(.+)",$/gm)].filter((m) => m[1][0] === (track === 'lld' ? 'L' : 'H')).map((m) => [m[1], m[2]]));

// SITE_URL comes from .env.deploy at deploy time (PLAN.md Section 14.2); never hard-code a host.
export default defineConfig({
  site: process.env.SITE_URL || undefined,
  base,
  // DESIGN_TRACKS_PLAN.md D10: Mermaid blocks become inline SVG at build time (no runtime network).
  // rehype-mermaid starts Chromium only when a page has a diagram, so builds without diagrams need no browser.
  markdown: {
    syntaxHighlight: { type: 'shiki', excludeLangs: ['mermaid'] },
    remarkPlugins: [remarkMath],
    rehypePlugins: [rehypeKatex, [rehypeMermaid, {
      // img-svg keeps the diagram's own styles with it. (inline-svg lost its <style> in MDX, so nodes and arrows
      // came out black.) Dark mode inverts the image in custom.css.
      strategy: 'img-svg',
      mermaidConfig: {
        theme: 'base',
        fontFamily: 'Helvetica, Arial, sans-serif',
        themeVariables: { primaryColor: '#e7effb', primaryTextColor: '#14213d', primaryBorderColor: '#3b6ea5', lineColor: '#44546a', secondaryColor: '#fdf3d7', tertiaryColor: '#eef6ee', fontSize: '15px', background: '#ffffff' },
        flowchart: { htmlLabels: false, curve: 'linear', padding: 14, nodeSpacing: 40, rankSpacing: 50 },
        sequence: { useMaxWidth: true, mirrorActors: false },
      },
    }]],
  },
  integrations: [
    starlight({
      title: 'CP Training',
      components: { Footer: './src/components/Footer.astro' },
      customCss: ['katex/dist/katex.min.css', './src/styles/custom.css'],
      head: [{ tag: 'script', attrs: { src: `${base.replace(/\/$/, '')}/later-badge.js`, defer: true } }],
      sidebar: [
        { label: 'Home', link: '/' },
        { label: 'Method', link: '/method/' },
        ...phaseGroups,
        { label: 'LLD: object design in C++', collapsed: true, items: [...designPhases('lld', phaseNames('lld')), { label: 'Pattern Handbook', link: '/lld/handbook/' }] },
        { label: 'HLD: system design with Go labs', collapsed: true, items: [...designPhases('hld', phaseNames('hld')), { label: 'Component Handbook', link: '/hld/handbook/' }, { label: 'Labs', link: '/hld/labs/' }, { label: 'Numbers sheet', link: '/hld/numbers/' }] },
        { label: 'Recognition Handbook', link: '/handbook/' },
        { label: 'Glossary', link: '/glossary/' },
        { label: 'Problems', link: '/problems/' },
        { label: 'Problem bank', link: '/bank/' },
        { label: 'Contest log', link: '/contests/' },
        { label: 'Progress', link: '/progress/' },
        { label: 'Profiles', link: '/profiles/' },
      ],
    }),
    react(),
  ],
});
