// The LeetCode console snippet (PROFILE_SYNC_PLAN.md Section 8), generated from a template with the site URL and the
// learner's username filled in. Written from the S0 probe output of 2026-10-13: the list query below works with and
// without the csrftoken header, returns `titleSlug` and `status` per problem, and its AC and TRIED filters give the
// solved and attempted problems directly. The text is plain and commented so the learner can read what they run, and
// names no problem (Section 15, Y4).

const TEMPLATE = String.raw`// CP Training: read your LeetCode problem statuses (read-only).
// It asks leetcode.com, as you (this page, your logged-in session), which problems you solved and which you
// tried without solving. At most one request per second, and it talks only to leetcode.com. It never reads or
// prints your session cookie; it only reads the public csrftoken value to send back to leetcode.com.
(async () => {
  const SITE = __SITE__; // the Profiles page that receives the result
  const USERNAME = __USER__;
  if (location.hostname !== 'leetcode.com') {
    console.log('Open https://leetcode.com in this browser first, then paste this again.');
    return;
  }
  const csrf = (document.cookie.match(/(?:^|; )csrftoken=([^;]*)/) || [])[1] || '';
  const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
  const query = 'query q($skip: Int, $limit: Int, $filters: QuestionListFilterInput) { ' +
    'problemsetQuestionList: questionList(categorySlug: "", limit: $limit, skip: $skip, filters: $filters) { ' +
    'total: totalNum questions: data { titleSlug status } } }';
  const statuses = {};

  // Pages through one filtered list (50 problems per request) and records every problem with the given label.
  async function collect(filter, label) {
    let skip = 0;
    let total = 1;
    while (skip < total) {
      await sleep(1100);
      const headers = { 'content-type': 'application/json' };
      if (csrf) headers['x-csrftoken'] = csrf;
      const res = await fetch('/graphql', {
        method: 'POST', headers, credentials: 'include',
        body: JSON.stringify({ query, variables: { skip, limit: 50, filters: { status: filter } } }),
      });
      const body = await res.json().catch(() => null);
      const list = body && body.data && body.data.problemsetQuestionList;
      if (!res.ok || !list || !Array.isArray(list.questions)) throw new Error('LeetCode changed; ask for an update');
      total = list.total;
      for (const q of list.questions) statuses[q.titleSlug] = label;
      skip += 50;
      console.log(label + ': ' + Math.min(skip, total) + ' of ' + total);
    }
  }

  try {
    await collect('TRIED', 'notac'); // attempted, not solved
    await collect('AC', 'ac');       // solved (wins if a problem is in both lists)
  } catch (e) {
    console.log(String(e.message || e));
    return;
  }
  if (Object.keys(statuses).length === 0) {
    console.log('No problems found. Are you logged in to leetcode.com in this browser?');
    return;
  }
  const payload = JSON.stringify({ v: 1, username: USERNAME, at: Math.floor(Date.now() / 1000), method: 'list', statuses });
  const link = SITE + '#lc=' + btoa(payload).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/, '');
  console.log('Done. Open this link to import (the part after # never leaves your browser):');
  console.log(link);
  try {
    copy(payload);
    console.log('The result was also copied: paste it into "Import a submissions file" on the Profiles page.');
  } catch (e) { /* copy() exists only in some consoles */ }
})();
`;

/** Snippet text for this learner. `siteUrl` is the absolute URL of the Profiles page. */
export function leetCodeSnippet(siteUrl: string, username: string): string {
  return TEMPLATE.replace('__SITE__', JSON.stringify(siteUrl)).replace('__USER__', JSON.stringify(username.trim()));
}
