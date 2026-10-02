// Practice set of one topic, grouped by tier, then pattern, with the learner's status
// (PROBLEM_BANK_PLAN.md Section 9.1). Receives practice problems only.
import { Fragment, useState } from 'react';
import { useProblems } from '../lib/useProblems';
import { STATUS_LABELS } from '../lib/storage';
import LogPanel from './LogPanel';

export type BankRow = { id: string; title: string; url: string; source: string; difficulty: string; pattern: string; apiOnly?: boolean };
export type BankTier = { tier: number; name: string; problems: BankRow[] };

const PLATFORM: Record<string, string> = { codeforces: 'Codeforces', atcoder: 'AtCoder', cses: 'CSES', leetcode: 'LeetCode' };

export default function BankTable({ tiers, patternNames }: { tiers: BankTier[]; patternNames: Record<string, string> }) {
  const logs = useProblems();
  const [open, setOpen] = useState<string | null>(null);
  const total = tiers.reduce((a, t) => a + t.problems.length, 0);
  if (!total) return <p>No practice problems have been collected for this topic yet.</p>;
  const anyApi = tiers.some((t) => t.problems.some((p) => p.apiOnly));

  return (
    <>
      {tiers.map((t) => (
        <section key={t.tier}>
          <h2 id={`tier-${t.tier}`}>Tier {t.tier}: {t.name}</h2>
          {t.problems.length === 0 ? (
            <p>No problems in this tier.</p>
          ) : (
            <div className="table-scroll">
              <table className="bank-table">
                <thead>
                  <tr><th>Problem</th><th>Platform</th><th>Difficulty</th><th>Pattern</th><th>Status</th><th /></tr>
                </thead>
                <tbody>
                  {t.problems.map((p) => {
                    const log = logs[p.id];
                    return (
                      <Fragment key={p.id}>
                        <tr className={log?.status ? `status-${log.status}` : undefined}>
                          <td>
                            <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a>
                            <div className="problem-id">{p.id}{p.apiOnly && <span title="Statement not checked by the bank builder; please spot-check"> †</span>}</div>
                          </td>
                          <td><span className={`badge badge-${p.source}`}>{PLATFORM[p.source]}</span></td>
                          <td>{p.difficulty}</td>
                          <td>{patternNames[p.pattern] ?? p.pattern}</td>
                          <td>{log?.status ? STATUS_LABELS[log.status] : 'Not started'}</td>
                          <td>
                            <button type="button" className="secondary" aria-expanded={open === p.id} onClick={() => setOpen(open === p.id ? null : p.id)}>
                              Log
                            </button>
                          </td>
                        </tr>
                        {open === p.id && (
                          <tr className="log-row-container">
                            <td colSpan={6}><LogPanel id={p.id} log={log} onDone={() => setOpen(null)} /></td>
                          </tr>
                        )}
                      </Fragment>
                    );
                  })}
                </tbody>
              </table>
            </div>
          )}
        </section>
      ))}
      {anyApi && <p className="muted">† Title and rating confirmed through the Codeforces API, but the statement could not be opened when the bank was built. Tell me in FEEDBACK.md if one doesn't fit its topic.</p>}
    </>
  );
}
