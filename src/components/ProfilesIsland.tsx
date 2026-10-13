// Profiles page island (PROFILE_SYNC_PLAN.md Section 11).
import { useEffect, useState } from 'react';
import { getProfiles, getSyncLog } from '../lib/sync/store';
import { applyImport, linkAtCoder, linkCodeforces, removeProfile, setLeetCodeUsername, syncPlatform, verifyCodeforces } from '../lib/sync/runner';
import { decodeLcFragment, parseImportText } from '../lib/sync/leetcode';
import { useStore } from '../lib/useStore';
import { leetCodeSnippet } from '../lib/sync/snippet';
import { url } from '../lib/url';
import { SYNC_EVENT } from '../lib/sync/store';

const TRANSPORT_LABEL: Record<string, string> = { direct: 'direct', jsonp: 'JSONP', proxy: 'proxy' };

function ago(sec?: number | null): string {
  if (!sec) return 'never';
  const m = Math.round((Date.now() / 1000 - sec) / 60);
  return m < 1 ? 'just now' : m < 60 ? `${m} minute${m === 1 ? '' : 's'} ago` : m < 1440 ? `${Math.round(m / 60)} hour${Math.round(m / 60) === 1 ? '' : 's'} ago` : `${Math.round(m / 1440)} day${Math.round(m / 1440) === 1 ? '' : 's'} ago`;
}
const exact = (sec?: number | null) => (sec ? new Date(sec * 1000).toLocaleString() : '');

function useRefresh() {
  const [, setN] = useState(0);
  useEffect(() => {
    const bump = () => setN((n) => n + 1);
    window.addEventListener(SYNC_EVENT, bump);
    return () => window.removeEventListener(SYNC_EVENT, bump);
  }, []);
}

function Card({ id, title, children }: { id: string; title: string; children: React.ReactNode }) {
  return (
    <section className="profile-card" aria-labelledby={`${id}-h`}>
      <h3 id={`${id}-h`}>{title}</h3>
      {children}
    </section>
  );
}

function Status({ at, error, transport }: { at?: number | null; error?: string | null; transport?: string | null }) {
  return (
    <>
      <p className="muted" title={exact(at)}>Last sync: {ago(at)}{transport ? ` · via ${TRANSPORT_LABEL[transport] ?? transport}` : ''}</p>
      {error && <p className="error" role="alert">Last error: {error}</p>}
    </>
  );
}

export default function ProfilesIsland() {
  const profiles = useStore(getProfiles, {});
  const log = useStore(getSyncLog, []);
  // Runs a sync and reports what happened, so the button never looks dead.
  async function syncMessage(p: 'cf' | 'ac'): Promise<string> {
    const r = await syncPlatform(p);
    if (r.error) return `Sync failed: ${r.error}`;
    return r.added > 0 ? `Synced: ${r.added} new submission${r.added === 1 ? '' : 's'}.` : 'Synced: already up to date, no new submissions.';
  }
  useRefresh();
  const [cf, setCf] = useState('');
  const [ac, setAc] = useState('');
  const [lc, setLc] = useState('');
  const [busy, setBusy] = useState<string | null>(null);
  const [msg, setMsg] = useState<Record<string, string>>({});
  const [paste, setPaste] = useState('');
  const [snippet, setSnippet] = useState('');
  const say = (k: string, v: string) => setMsg((m) => ({ ...m, [k]: v }));

  useEffect(() => {
    const p = getProfiles();
    setCf(p.codeforces?.handle ?? '');
    setAc(p.atcoder?.userId ?? '');
    setLc(p.leetcode?.username ?? '');
    // A `#lc=` link from the LeetCode snippet imports automatically; the fragment is then removed from the address bar.
    const json = decodeLcFragment(location.hash);
    if (json) {
      importText(json);
      history.replaceState(null, '', location.pathname + location.search);
    }
  }, []);

  async function importText(text: string, bytes?: number) {
    const r = parseImportText(text, bytes);
    if (r.kind === 'error') return say('import', r.message);
    say('import', await applyImport(r));
  }

  async function act(key: string, fn: () => Promise<string | null | void>, ok?: string) {
    setBusy(key);
    say(key, '');
    const err = await fn();
    say(key, err ?? ok ?? '');
    setBusy(null);
  }

  return (
    <div className="profile-grid">
      <Card id="cf" title="Codeforces">
        <label htmlFor="cf-handle">Codeforces handle</label>
        <input id="cf-handle" value={cf} onChange={(e) => setCf(e.target.value)} placeholder="tourist" autoComplete="off" spellCheck={false} />
        <div className="actions">
          <button type="button" disabled={!cf.trim() || busy === 'cf'} onClick={() => act('cf', () => linkCodeforces(cf), 'Saved and synced.')}>{busy === 'cf' ? 'Working…' : 'Save and sync'}</button>
          <button type="button" className="secondary" disabled={!profiles.codeforces || busy === 'cf'} onClick={() => act('cf', () => syncMessage('cf'))}>{busy === 'cf' ? 'Working…' : 'Sync now'}</button>
          <button type="button" className="secondary" disabled={!cf.trim() || busy === 'cf'} onClick={() => act('cf', async () => { const r = await verifyCodeforces(cf); return r.error ?? `Handle found: ${r.handle}.`; })}>Verify</button>
          <button type="button" className="secondary" disabled={!profiles.codeforces} onClick={() => { if (confirm('This removes the handle and its cached submissions. Your own log is not affected.')) { removeProfile('codeforces'); setCf(''); say('cf', 'Removed.'); } }}>Remove</button>
        </div>
        {profiles.codeforces && <Status at={profiles.codeforces.lastSyncAt} error={profiles.codeforces.lastError} transport={profiles.codeforces.transport} />}
        {msg.cf && <p role="status">{msg.cf}</p>}
      </Card>

      <Card id="ac" title="AtCoder">
        <label htmlFor="ac-user">AtCoder user id</label>
        <input id="ac-user" value={ac} onChange={(e) => setAc(e.target.value)} placeholder="tourist" autoComplete="off" spellCheck={false} />
        <p className="muted">Submissions come from AtCoder Problems (an unofficial service), so very recent submissions may take a while to appear.</p>
        <div className="actions">
          <button type="button" disabled={!ac.trim() || busy === 'ac'} onClick={() => act('ac', () => linkAtCoder(ac), 'Saved and synced.')}>Save and sync</button>
          <button type="button" className="secondary" disabled={!profiles.atcoder || busy === 'ac'} onClick={() => act('ac', () => syncMessage('ac'))}>{busy === 'ac' ? 'Working…' : 'Sync now'}</button>
          <button type="button" className="secondary" disabled={!profiles.atcoder} onClick={() => { if (confirm('This removes the user id and its cached submissions. Your own log is not affected.')) { removeProfile('atcoder'); setAc(''); say('ac', 'Removed.'); } }}>Remove</button>
        </div>
        {profiles.atcoder && <Status at={profiles.atcoder.lastSyncAt} error={profiles.atcoder.lastError} transport={profiles.atcoder.transport} />}
        {msg.ac && <p role="status">{msg.ac}</p>}
      </Card>

      <Card id="lc" title="LeetCode">
        <label htmlFor="lc-user">LeetCode username</label>
        <input id="lc-user" value={lc} onChange={(e) => setLc(e.target.value)} placeholder="your-username" autoComplete="off" spellCheck={false} />
        <div className="actions">
          <button type="button" disabled={!lc.trim()} onClick={() => { setLeetCodeUsername(lc); say('lc', 'Saved.'); }}>Save</button>
          <button type="button" className="secondary" disabled={!profiles.leetcode} onClick={() => { if (confirm('This removes the username and its imported statuses. Your own log is not affected.')) { removeProfile('leetcode'); setLc(''); say('lc', 'Removed.'); } }}>Remove</button>
        </div>
        <p className="muted" title={exact(profiles.leetcode?.lastImportAt)}>Last import: {ago(profiles.leetcode?.lastImportAt)}</p>
        <div className="actions">
          <button type="button" disabled={!lc.trim()} onClick={async () => {
            const text = leetCodeSnippet(location.origin + url('/profiles/'), lc);
            setSnippet(text);
            try { await navigator.clipboard.writeText(text); say('lc', 'Snippet copied. Follow the steps below.'); } catch { say('lc', 'Could not copy automatically: select the snippet below and copy it.'); }
          }}>Copy LeetCode snippet</button>
        </div>
        <p>
          LeetCode has no public API for your full history, so statuses arrive from a short snippet that you run yourself on
          leetcode.com while logged in. It reads only which problems you solved or tried, makes at most one request per second,
          and never reads your session cookie. <strong>It needs a desktop browser with developer tools.</strong>
        </p>
        <ol>
          <li>Enter your username above and press <em>Copy LeetCode snippet</em>.</li>
          <li>Open <a href="https://leetcode.com" target="_blank" rel="noopener noreferrer">leetcode.com</a> in the same browser, logged in, and open the developer tools console (F12, then Console).</li>
          <li>Paste the snippet and press Enter. Wait until it prints <em>Done</em>.</li>
          <li>Open the link it prints (or paste the copied result into <em>Import a submissions file</em> below). The statuses appear within seconds.</li>
        </ol>
        {snippet && <details><summary>Show the snippet</summary><pre><code>{snippet}</code></pre></details>}
        {msg.lc && <p role="status">{msg.lc}</p>}
      </Card>

      <Card id="import" title="Import a submissions file">
        <p>Accepts a LeetCode snippet result, a Codeforces <code>user.status</code> response, or an AtCoder Problems submissions list saved from the address bar (for when no automatic route works). Files over 5 MB are refused.</p>
        <label htmlFor="import-file">File</label>
        <input id="import-file" type="file" accept=".json,application/json" onChange={async (e) => { const f = e.target.files?.[0]; if (f) await importText(await f.text(), f.size); e.target.value = ''; }} />
        <label htmlFor="import-paste">Or paste the JSON</label>
        <textarea id="import-paste" rows={4} value={paste} onChange={(e) => setPaste(e.target.value)} />
        <div className="actions"><button type="button" disabled={!paste.trim()} onClick={async () => { await importText(paste); setPaste(''); }}>Import pasted JSON</button></div>
        {msg.import && <p role="status">{msg.import}</p>}
      </Card>

      <details>
        <summary>Sync log (last 20 runs)</summary>
        {log.length === 0 ? <p>No runs yet.</p> : (
          <div className="table-scroll">
            <table className="bank-table">
              <thead><tr><th>When</th><th>Platform</th><th>Route</th><th>Requests</th><th>New</th><th>ms</th><th>Result</th></tr></thead>
              <tbody>
                {[...log].reverse().map((r, i) => (
                  <tr key={i}><td>{exact(r.at)}</td><td>{r.platform}</td><td>{r.transport ?? '—'}</td><td>{r.requests}</td><td>{r.newSubmissions}</td><td>{r.ms}</td><td>{r.error ?? r.note ?? 'ok'}</td></tr>
                ))}
              </tbody>
            </table>
          </div>
        )}
      </details>
    </div>
  );
}
