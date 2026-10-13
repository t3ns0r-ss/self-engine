// React side of status.ts: re-reads logs, caches and profiles whenever storage or a sync changes.
import { useCallback, useEffect, useState } from 'react';
import { getProblems } from '../storage';
import { useStore } from '../useStore';
import { CF_ALIASES } from './aliases';
import { lookup, type Entry } from './core';
import { getCaches, getProfiles, getShown, SYNC_EVENT } from './store';
import { compromisedIn } from './reserved';
import { computeStatus, type StatusView } from './status';

function useCaches() {
  // Caches are bigger than the other stores, so they reload only on the sync event and storage events.
  const [caches, setCaches] = useState<ReturnType<typeof getCaches>>({});
  useEffect(() => {
    const load = () => setCaches(getCaches());
    load();
    window.addEventListener(SYNC_EVENT, load);
    window.addEventListener('storage', load);
    window.addEventListener('cp-storage-change', load);
    return () => {
      window.removeEventListener(SYNC_EVENT, load);
      window.removeEventListener('storage', load);
      window.removeEventListener('cp-storage-change', load);
    };
  }, []);
  return caches;
}

export function useSync() {
  const logs = useStore(getProblems, {});
  const profiles = useStore(getProfiles, {});
  const caches = useCaches();
  const status = useCallback((id: string): StatusView => computeStatus(id, logs[id], caches, profiles, CF_ALIASES), [logs, caches, profiles]);
  const entry = useCallback((id: string): Entry | undefined => lookup(id, caches, CF_ALIASES), [caches]);
  return { status, entry, profiles, caches, logs };
}

/** Returns getStatus(problemId) for the current storage; components re-render on any change. */
export const useStatuses = (): ((id: string) => StatusView) => useSync().status;

export type { StatusView };

/** Compromised reserved problems among `ids` (Section 10.2), judged against when each was first shown. */
export function useCompromised(ids: string[]): Set<string> {
  const { caches } = useSync();
  const shown = useStore(getShown, {});
  return compromisedIn(ids, caches, shown);
}
