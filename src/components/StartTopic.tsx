// Marks a topic as the learner's current topic (dashboard uses it).
import { getSettings, getTopics, saveSettings, saveTopic, today } from '../lib/storage';
import { useStore } from '../lib/useStore';

export default function StartTopic({ topic }: { topic: string }) {
  const current = useStore(() => getSettings().currentTopic ?? null, null);
  if (current === topic) return <p className="muted">This is your current topic.</p>;
  return (
    <button
      type="button"
      className="secondary"
      onClick={() => {
        if (!getTopics()[topic]?.started) saveTopic(topic, { started: today() });
        saveSettings({ currentTopic: topic });
      }}
    >
      Make this my current topic
    </button>
  );
}
