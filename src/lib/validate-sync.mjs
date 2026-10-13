// Build-time checks for profile sync (PROFILE_SYNC_PLAN.md Section 15, Y1 to Y4). Pure functions; scripts/check_sync.mjs
// feeds them the real files.

/** Y1: the alias file has an entry for every Codeforces key used on the site. */
export function checkAliases(siteKeys, aliases) {
  const missing = siteKeys.filter((k) => !Object.hasOwn(aliases, k));
  return missing.length
    ? [`src/data/sync/cf-aliases.json has no entry for ${missing.length} Codeforces key(s) (first: ${missing.slice(0, 5).join(', ')}): run node scripts/cf_aliases.mjs`]
    : [];
}

/**
 * Y2: no component reads a problem's `.status` from cp:v1:problems directly. Everything must go through getStatus
 * (src/lib/sync). Allowed: the log panel (it edits the learner's own entry) and the storage and sync modules themselves.
 * files: [{ path, text }].
 */
const ALLOWED_STATUS_READERS = [/^src\/lib\/storage\.ts$/, /^src\/lib\/sync\//, /^src\/components\/LogPanel\.tsx$/];
const DIRECT_STATUS = /\b(?:logs?|problems?|getProblems\(\))(?:\[[^\]]+\])?\??\.status\b/;
export function checkStatusReads(files) {
  const errors = [];
  for (const f of files) {
    if (ALLOWED_STATUS_READERS.some((re) => re.test(f.path))) continue;
    f.text.split('\n').forEach((line, i) => {
      if (DIRECT_STATUS.test(line)) errors.push(`${f.path}:${i + 1}: reads a problem's status directly; use getStatus / useStatuses from src/lib/sync (${line.trim()})`);
    });
  }
  return errors;
}

/** Y3: public/sync-config.json is valid, and proxyBase is null unless SYNC_PROXY_BASE is set. */
export function checkSyncConfig(text, env = {}) {
  let cfg;
  try {
    cfg = JSON.parse(text);
  } catch {
    return ['public/sync-config.json is missing or not valid JSON: run node scripts/write_sync_config.mjs'];
  }
  if (!cfg || typeof cfg !== 'object' || !('proxyBase' in cfg)) return ['public/sync-config.json needs a proxyBase field'];
  const want = env.SYNC_PROXY_BASE || null;
  if (cfg.proxyBase !== want) return [`public/sync-config.json has proxyBase ${JSON.stringify(cfg.proxyBase)} but SYNC_PROXY_BASE says ${JSON.stringify(want)}`];
  return [];
}

/** Y4: the generated LeetCode snippet names no reserved LeetCode problem. reservedSlugs: Set of slugs. */
export function checkSnippetSlugs(snippetText, reservedSlugs) {
  return [...reservedSlugs].filter((slug) => snippetText.includes(slug)).map((slug) => `LeetCode snippet text contains the reserved problem "${slug}"`);
}
