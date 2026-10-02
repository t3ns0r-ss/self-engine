// React hook: the stored problem logs, re-read whenever any island (or another tab) changes them.
import { useEffect, useState } from 'react';
import { CHANGE_EVENT, KEYS, getProblems, type ProblemLog } from './storage';

export function useProblems(): Record<string, ProblemLog> {
  // Start empty so the server render and the first client render match; load after mount.
  const [logs, setLogs] = useState<Record<string, ProblemLog>>({});
  useEffect(() => {
    const load = () => setLogs(getProblems());
    const onStorage = (e: StorageEvent) => {
      if (e.key === null || e.key === KEYS.problems) load();
    };
    load();
    window.addEventListener(CHANGE_EVENT, load);
    window.addEventListener('storage', onStorage);
    return () => {
      window.removeEventListener(CHANGE_EVENT, load);
      window.removeEventListener('storage', onStorage);
    };
  }, []);
  return logs;
}
