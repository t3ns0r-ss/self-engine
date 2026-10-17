// Build-time access to design code units, lab files, kit READMEs and experiment results (DESIGN_TRACKS_PLAN.md Section 11.7).
// import.meta.glob reads the files when the site is built; '?raw' gives the file text. Patterns are narrow on purpose:
// the code/ folder also holds hundreds of CP files that design pages never show.
import { parse } from 'yaml';

const codeFiles = import.meta.glob('/code/[LH]*/**/*.{go,cpp,hpp,txt,tsv,md,yaml,sh}', { query: '?raw', import: 'default' }) as Record<string, () => Promise<string>>;
const refFiles = import.meta.glob('/reference/**/SOLUTION.md', { query: '?raw', import: 'default' }) as Record<string, () => Promise<string>>;
const experimentFiles = import.meta.glob('/src/data/experiments/**/*.yaml', { query: '?raw', import: 'default', eager: true }) as Record<string, string>;

/** Paths (relative to code/) of the files of a unit folder such as "L2.1/strategy-fee". */
export function unitFileList(unit: string): string[] {
  const prefix = `/code/${unit}/`;
  return Object.keys(codeFiles).filter((p) => p.startsWith(prefix)).map((p) => p.slice('/code/'.length)).sort();
}
export async function readCode(rel: string): Promise<string | undefined> {
  const f = codeFiles[`/code/${rel}`];
  return f ? await f() : undefined;
}
export async function readSolution(kitPath: string): Promise<string | undefined> {
  const f = refFiles[`/reference/${kitPath}/SOLUTION.md`];
  return f ? await f() : undefined;
}
export const langOf = (file: string) => (file.endsWith('.go') ? 'go' : /\.(cpp|hpp)$/.test(file) ? 'cpp' : file.endsWith('.sh') ? 'bash' : file.endsWith('.yaml') ? 'yaml' : 'text');

export type LabInfo = { unit: string; title: string; holds: string[]; breaks: string[]; run: string; experiments: string[]; stacks: string[] };
/** Every lab.yaml under code/H*, parsed. */
export async function allLabs(): Promise<LabInfo[]> {
  const out: LabInfo[] = [];
  for (const [p, load] of Object.entries(codeFiles)) {
    if (!p.endsWith('/lab.yaml')) continue;
    out.push({ unit: p.slice('/code/'.length, -'/lab.yaml'.length), ...(parse(await load()) as Omit<LabInfo, 'unit'>) });
  }
  return out.sort((a, b) => a.unit.localeCompare(b.unit, undefined, { numeric: true }));
}

export type ExperimentRecord = { experiment: string; program: string; machine: { cpu: string; cores: number; os: string; go: string }; run_on: string; commit: string; shape_checks: string[]; results_file: string };
export function experimentRecord(id: string): ExperimentRecord | undefined {
  for (const text of Object.values(experimentFiles)) {
    const r = parse(text) as ExperimentRecord;
    if (r.experiment === id) return r;
  }
  return undefined;
}

/** Parses a tab-separated table: first line is the header unless `header` is given. */
export function parseTsv(text: string): string[][] {
  return text.trim().split('\n').map((l) => l.split('\t'));
}
