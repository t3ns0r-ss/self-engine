#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.4.4. Events (first day, last day), one event a day. Sweep the days; the heap holds the last days of the events that have
// started and have not been attended; each day attend the event with the earliest last day (events whose last day has passed are dropped).
int mostEvents(vector<pair<int, int>> events) {
    sort(events.begin(), events.end());
    priority_queue<int, vector<int>, greater<int>> open;
    int attended = 0;
    size_t next = 0;
    for (int day = 1; next < events.size() || !open.empty(); day++) {
        if (open.empty()) day = max(day, events[next].first);  // nothing to do before the next event starts
        while (next < events.size() && events[next].first <= day) open.push(events[next++].second);
        while (!open.empty() && open.top() < day) open.pop();
        if (!open.empty()) open.pop(), attended++;
    }
    return attended;
}
// snippet:end

int bruteEvents(const vector<pair<int, int>>& events) {  // the largest matching of events to days (augmenting paths)
    int days = 0;
    for (auto& e : events) days = max(days, e.second);
    vector<int> owner(days + 1, -1);
    function<bool(int, vector<char>&)> assign = [&](int e, vector<char>& seen) {
        for (int d = events[e].first; d <= events[e].second; d++) {
            if (seen[d]) continue;
            seen[d] = 1;
            if (owner[d] < 0 || assign(owner[d], seen)) return owner[d] = e, true;
        }
        return false;
    };
    int count = 0;
    for (size_t e = 0; e < events.size(); e++) {
        vector<char> seen(days + 1, 0);
        count += assign(e, seen);
    }
    return count;
}

int main() {
    cout << "events 1: " << mostEvents({{1, 2}, {2, 3}, {3, 4}}) << "\n";
    cout << "events 2: " << mostEvents({{1, 2}, {2, 3}, {3, 4}, {1, 2}}) << "\n";
    cout << "events 3: " << mostEvents({{1, 2}, {1, 2}, {1, 2}, {1, 2}}) << "\n";
    // Check (not printed): 3000 random sets of up to 8 events on up to 9 days, against the largest matching.
    mt19937 rng(24);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 8 + 1;
        vector<pair<int, int>> e(n);
        for (auto& [a, b] : e) a = rng() % 9 + 1, b = a + rng() % 4;
        if (mostEvents(e) != bruteEvents(e)) return 1;
    }
}
