// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import react from '@astrojs/react';
import remarkMath from 'remark-math';
import rehypeKatex from 'rehype-katex';

// SITE_URL comes from .env.deploy at deploy time (PLAN.md Section 14.2); never hard-code a host.
export default defineConfig({
  site: process.env.SITE_URL || undefined,
  markdown: { remarkPlugins: [remarkMath], rehypePlugins: [rehypeKatex] },
  integrations: [
    starlight({
      title: 'CP Training',
      customCss: ['katex/dist/katex.min.css', './src/styles/custom.css'],
      sidebar: [
        { label: 'Home', link: '/' },
        { label: 'Problem bank', link: '/bank/' },
      ],
    }),
    react(),
  ],
});
