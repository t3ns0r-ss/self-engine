#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.6. The largest number of half-open intervals [s, e) that cover one point: sort the events
// (time, +1 at a start, -1 at an end); at equal times -1 comes first.
int maxCoverage(const vector<pair<int, int>>& intervals) {
    vector<pair<int, int>> events;
    for (auto [s, e] : intervals) events.push_back({s, +1}), events.push_back({e, -1});
    sort(events.begin(), events.end());
    int cur = 0, best = 0;
    for (auto [time, change] : events) {
        cur += change;
        best = max(best, cur);
    }
    return best;
}
// snippet:end

int main() {
    cout << "[1,4) [2,5) [4,6): " << maxCoverage({{1, 4}, {2, 5}, {4, 6}}) << '\n';
    cout << "[1,3) [3,5): " << maxCoverage({{1, 3}, {3, 5}}) << '\n';
    cout << "[1,10) [2,3) [4,5): " << maxCoverage({{1, 10}, {2, 3}, {4, 5}}) << '\n';
    mt19937 rng(12);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 6 + 1;
        vector<pair<int, int>> iv(n);
        for (auto& p : iv) { p.first = rng() % 10; p.second = p.first + 1 + rng() % 6; }
        int best = 0;
        for (int t = 0; t < 20; t++) {
            int c = 0;
            for (auto [s, e] : iv) c += s <= t && t < e;
            best = max(best, c);
        }
        if (best != maxCoverage(iv)) return 1;
    }
}
