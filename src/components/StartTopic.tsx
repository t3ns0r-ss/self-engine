// Marks a topic as the learner's current topic (dashboard uses it).
import { getCurrentTopic, getTopics, saveTopic, setCurrentTopic, today, type Track } from '../lib/storage';
import { useStore } from '../lib/useStore';

export default function StartTopic({ topic, track = 'cp' }: { topic: string; track?: Track }) {
  const current = useStore(() => getCurrentTopic(track) ?? null, null);
  if (current === topic) return <p className="muted">This is your current topic.</p>;
  return (
    <button
      type="button"
      className="secondary"
      onClick={() => {
        if (!getTopics()[topic]?.started) saveTopic(topic, { started: today() });
        setCurrentTopic(track, topic);
      }}
    >
      Make this my current topic
    </button>
  );
}
