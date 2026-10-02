// React hook: the stored problem logs, kept in sync across islands and tabs.
import { getProblems, type ProblemLog } from './storage';
import { useStore } from './useStore';

export const useProblems = (): Record<string, ProblemLog> => useStore(getProblems, {});
