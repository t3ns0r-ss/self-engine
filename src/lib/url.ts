// Internal links must include the site's base path (e.g. /self-engine/ on GitHub Pages).
// url('/bank/') -> '/self-engine/bank/'. Works in Astro components and in React islands.
const BASE = import.meta.env.BASE_URL.replace(/\/$/, '');
export const url = (path: string) => `${BASE}${path}`;
