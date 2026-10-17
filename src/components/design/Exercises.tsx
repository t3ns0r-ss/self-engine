// The ladder list of a topic (Section 11.7): rung, title, new force, status from the attempt log, link to the exercise page.
import { useEffect, useState } from 'react';
import { getDesignAttempts } from '../../lib/storage';
import { url } from '../../lib/url';
import { useStore } from '../../lib/useStore';

export type LadderItem = { globalId: string; id: string; rung: number | null; title: string; newForce: string | null; href: string; type: string; role: string };

export default function Exercises({ topic }: { topic: string }) {
  const attempts = useStore(getDesignAttempts, {});
  const [items, setItems] = useState<LadderItem[] | null>(null);
  const [err, setErr] = useState('');
  useEffect(() => {
    fetch(url(`/data/practice/${encodeURIComponent(topic)}.json`)).then((r) => (r.ok ? r.json() : Promise.reject(new Error(`HTTP ${r.status}`)))).then((all: LadderItem[]) => setItems(all.filter((i) => i.role === 'ladder'))).catch((e) => setErr(e.message));
  }, [topic]);
  if (err) return <p className="notice">Could not load the exercises: {err}</p>;
  if (!items) return <p>Loading…</p>;
  if (!items.length) return <p className="muted">No practice exercises yet.</p>;
  return (
    <ol className="design-ladder">
      {items.map((i) => {
        const a = attempts[i.globalId] ?? [];
        const done = a.some((x) => x.testsPassed);
        return (
          <li key={i.globalId}>
            <p>
              <a href={i.href}><strong>{i.rung ? `Rung ${i.rung}: ` : ''}{i.title}</strong></a>{' '}
              <span className={`status ${done ? 'status-done' : a.length ? 'status-started' : ''}`}>{done ? 'passed' : a.length ? `${a.length} attempt${a.length === 1 ? '' : 's'}` : 'not started'}</span>
            </p>
            {i.newForce && <p className="muted">New force: {i.newForce}</p>}
          </li>
        );
      })}
    </ol>
  );
}
