/** The lines between `// snippet:begin` and `// snippet:end` of a code unit, or null when the markers are missing. */
export function snippetOf(source: string): string | null {
  const lines = source.split('\n');
  const a = lines.findIndex((l) => l.trim() === '// snippet:begin');
  const b = lines.findIndex((l) => l.trim() === '// snippet:end');
  if (a < 0 || b < a) return null;
  return lines.slice(a + 1, b).join('\n').trimEnd();
}
