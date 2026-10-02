const NAMES: Record<string, string> = { codeforces: 'Codeforces', atcoder: 'AtCoder', cses: 'CSES', leetcode: 'LeetCode' };
export default function PlatformBadge({ source }: { source: string }) {
  return <span className={`badge badge-${source}`}>{NAMES[source] ?? source}</span>;
}
