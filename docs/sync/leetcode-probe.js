// LeetCode probe (PROFILE_SYNC_PLAN.md Section 8.2). READ-ONLY: it only asks LeetCode questions about YOUR OWN
// problem statuses, at most one request per second, and prints counts, field names and three example slugs.
// It never reads or prints your session cookie. It does read the public `csrftoken` cookie value, only to send it
// back to leetcode.com in a header if the request needs it.
//
// How to run: open https://leetcode.com in a desktop browser where you are logged in, open the developer tools
// console (F12 -> Console), paste this whole file, press Enter, then paste everything it prints back to Claude.
(async () => {
  const csrf = (document.cookie.match(/(?:^|; )csrftoken=([^;]*)/) || [])[1] || '';
  const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
  const results = [];

  // Sends one GraphQL query to leetcode.com (same origin, your own session).
  async function ask(label, query, variables, withCsrf) {
    await sleep(1100);
    const headers = { 'content-type': 'application/json' };
    if (withCsrf && csrf) headers['x-csrftoken'] = csrf;
    try {
      const res = await fetch('/graphql', { method: 'POST', headers, credentials: 'include', body: JSON.stringify({ query, variables }) });
      const body = await res.json().catch(() => null);
      const errors = body && body.errors ? body.errors.map((e) => String(e.message).slice(0, 120)) : null;
      results.push({ label, withCsrf, http: res.status, ok: !!(body && body.data && !errors), errors, data: body && body.data });
    } catch (e) {
      results.push({ label, withCsrf, http: 0, ok: false, errors: [String(e).slice(0, 120)] });
    }
  }

  // Candidate 1: a paged problem list that carries a status per problem (preferred).
  const list = `query q($skip: Int, $limit: Int, $filters: QuestionListFilterInput) {
    problemsetQuestionList: questionList(categorySlug: "", limit: $limit, skip: $skip, filters: $filters) {
      total: totalNum questions: data { titleSlug status }
    } }`;
  await ask('list, no filter', list, { skip: 0, limit: 5, filters: {} }, false);
  await ask('list, no filter', list, { skip: 0, limit: 5, filters: {} }, true);
  await ask('list, status filter AC', list, { skip: 0, limit: 5, filters: { status: 'AC' } }, true);
  await ask('list, status filter TRIED', list, { skip: 0, limit: 5, filters: { status: 'TRIED' } }, true);

  // Candidate 2: one problem by slug (fallback).
  const one = 'query q($titleSlug: String!) { question(titleSlug: $titleSlug) { titleSlug status } }';
  await ask('single problem', one, { titleSlug: 'two-sum' }, true);

  // Print only what Claude needs: which candidates worked, and field names, counts and three example slugs.
  const out = results.map((r) => {
    const q = r.data && (r.data.problemsetQuestionList || r.data.question);
    const items = q && (q.questions || (q.titleSlug ? [q] : []));
    return {
      label: r.label, sentCsrf: r.withCsrf, http: r.http, ok: r.ok, errors: r.errors,
      total: q && q.total, fields: items && items[0] ? Object.keys(items[0]) : null,
      statusValuesSeen: items ? [...new Set(items.map((i) => i.status))] : null,
      exampleSlugs: items ? items.slice(0, 3).map((i) => i.titleSlug) : null,
    };
  });
  const text = JSON.stringify(out, null, 1);
  console.log(text);
  try { copy(text); console.log('(Copied to the clipboard.)'); } catch (e) { console.log('(copy() is not available in this console; select and copy the output above.)'); }
})();
