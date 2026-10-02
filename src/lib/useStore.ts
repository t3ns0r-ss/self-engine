// React hook: re-reads a storage getter whenever any island (or another tab) changes storage.
import { useEffect, useState } from 'react';
import { CHANGE_EVENT } from './storage';

export function useStore<T>(getter: () => T, initial: T): T {
  // Start from `initial` so the server render and the first client render match.
  const [value, setValue] = useState<T>(initial);
  useEffect(() => {
    const load = () => setValue(getter());
    load();
    window.addEventListener(CHANGE_EVENT, load);
    window.addEventListener('storage', load);
    return () => {
      window.removeEventListener(CHANGE_EVENT, load);
      window.removeEventListener('storage', load);
    };
  }, []);
  return value;
}
