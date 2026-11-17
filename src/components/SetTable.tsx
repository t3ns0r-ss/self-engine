// A contest-practice problem set (volume set, bridge set) as a table with the learner's status (CURRICULUM_GAPS_PLAN.md Section 6, items 2 and 3).
// The sets are not topics: rows carry their own text, status comes from the same sources as every other problem list.
import { Fragment, useState } from 'react';
import { useProblems } from '../lib/useProblems';
import { useStatuses } from '../lib/sync/useStatuses';
import { isSolvedView } from '../lib/sync/status';
import StatusChip from './StatusChip';
import LogPanel from './LogPanel';

export type SetRow = {
  id: string; title: string; url: string; source: string; difficulty: string; summary: string; apiOnly?: boolean;
  topicLabel?: string; topicHref?: string;   // volume set: the earliest topic that gives what the problem needs
  have?: string; newIdea?: string;           // bridge set
};

const PLATFORM: Record<string, string> = { codeforces: 'Codeforces', atcoder: 'AtCoder', cses: 'CSES', leetcode: 'LeetCode' };

export default function SetTable({ rows, kind }: { rows: SetRow[]; kind: 'volume' | 'bridge' }) {
  const logs = useProblems();
  const st = useStatuses();
  const [open, setOpen] = useState<string | null>(null);
  const done = rows.filter((r) => isSolvedView(st(r.id))).length;
  const anyApi = rows.some((r) => r.apiOnly);
  const cols = kind === 'volume' ? 6 : 7;

  return (
    <>
      <p className="muted" aria-live="polite">{done} of {rows.length} solved.</p>
      <div className="table-scroll">
        <table className="bank-table">
          <thead>
            <tr>
              <th>Problem</th><th>Platform</th><th>Difficulty</th>
              {kind === 'volume' ? <th>Earliest topic</th> : <><th>What you have</th><th>The one new idea (a spoiler)</th></>}
              <th>Status</th><th />
            </tr>
          </thead>
          <tbody>
            {rows.map((p) => (
              <Fragment key={p.id}>
                <tr className={st(p.id).status ? `status-${st(p.id).status}` : undefined}>
                  <td>
                    <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a>
                    {p.apiOnly && <span title="Statement could not be opened when the set was built; the summary is recalled. Please spot-check."> †</span>}
                    <div className="muted">{p.summary}</div>
                    <div className="problem-id">{p.id}</div>
                  </td>
                  <td><span className={`badge badge-${p.source}`}>{PLATFORM[p.source]}</span></td>
                  <td>{p.difficulty}</td>
                  {kind === 'volume' ? (
                    <td>{p.topicHref ? <a href={p.topicHref}>{p.topicLabel}</a> : p.topicLabel}</td>
                  ) : (
                    <><td>{p.have}</td><td><details><summary>Show the new idea</summary>{p.newIdea}</details></td></>
                  )}
                  <td><StatusChip view={st(p.id)} /></td>
                  <td>
                    <button type="button" className="secondary" aria-expanded={open === p.id} onClick={() => setOpen(open === p.id ? null : p.id)}>
                      Log
                    </button>
                  </td>
                </tr>
                {open === p.id && (
                  <tr className="log-row-container">
                    <td colSpan={cols}><LogPanel id={p.id} log={logs[p.id]} onDone={() => setOpen(null)} /></td>
                  </tr>
                )}
              </Fragment>
            ))}
          </tbody>
        </table>
      </div>
      {anyApi && <p className="muted">† Title and rating confirmed through the Codeforces API, but the statement could not be opened, so the summary is recalled from memory. Tell me in FEEDBACK.md if one is wrong.</p>}
    </>
  );
}
