// Validation of the contest-practice data that lives outside curriculum.yaml (CURRICULUM_GAPS_PLAN.md Section 6):
// implementation drills (src/data/drills.yaml) and the optional "read one accepted solution" prompt of a topic file.
// `exists(path)` tells whether a path (relative to the repository root) exists.
export const DRILL_MIN = 8;
export const DRILL_MAX = 12;
export const READ_SOLUTION_FIRST_PHASE = 3;

export function validateDrills({ curriculum, topics, drills }, exists) {
  const errors = [];
  const D = 'src/data/drills.yaml';
  const byId = new Map(curriculum.filter((t) => !t.draft).map((t) => [t.id, t]));
  if (drills.length < DRILL_MIN || drills.length > DRILL_MAX) errors.push(`${D}: ${drills.length} drills, expected ${DRILL_MIN} to ${DRILL_MAX}`);
  const ids = new Set();
  const units = new Set();
  for (const d of drills) {
    if (ids.has(d.id)) errors.push(`${D}: duplicate drill id ${d.id}`);
    ids.add(d.id);
    if (units.has(d.unit)) errors.push(`${D}: drill ${d.id}: unit ${d.unit} is used by another drill`);
    units.add(d.unit);
    if (!byId.has(d.topic)) errors.push(`${D}: drill ${d.id}: unknown or draft topic ${d.topic}`);
    if (!d.unit.startsWith(`${d.topic}/`)) errors.push(`${D}: drill ${d.id}: unit ${d.unit} must live under code/${d.topic}/`);
    if (!d.unit.includes('/drill-')) errors.push(`${D}: drill ${d.id}: unit folder name must start with "drill-"`);
    const dir = `code/${d.unit}`;
    for (const f of ['solution.cpp', 'brute.cpp', 'gen.cpp', 'tests/1.in', 'tests/1.out'])
      if (!exists(`${dir}/${f}`)) errors.push(`${D}: drill ${d.id}: missing ${dir}/${f}`);
  }
  for (const [tid, tf] of Object.entries(topics)) {
    if (!tf.read_solution) continue;
    const t = byId.get(tid);
    if (t && t.phase < READ_SOLUTION_FIRST_PHASE) errors.push(`src/data/topics/${tid.replace('.', '-')}.yaml: read_solution is for Phase ${READ_SOLUTION_FIRST_PHASE} onwards, topic ${tid} is in Phase ${t.phase}`);
  }
  return errors;
}
