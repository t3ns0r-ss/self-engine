// Inline text with `$maths$` and `code` rendered. Use for text that comes from data files.
import { mathText } from '../lib/mathText';
export default function M({ t }: { t: string }) {
  return <span dangerouslySetInnerHTML={{ __html: mathText(t) }} />;
}
