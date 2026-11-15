#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.6. Half-open intervals [l, r): one scan over the sorted events gives, for every k, how many integer points
// lie in at least k intervals. The pair order puts an end (-1) before a start (+1) at the same position.
vector<long long> coveredAtLeast(const vector<pair<int, int>>& intervals) {
    int n = intervals.size();
    vector<pair<int, int>> events;  // (position, +1 at l / -1 at r)
    for (auto [l, r] : intervals) events.push_back({l, +1}), events.push_back({r, -1});
    sort(events.begin(), events.end());
    vector<long long> exact(n + 1, 0);  // exact[c] = points covered by exactly c intervals
    int count = 0;
    for (size_t t = 0; t + 1 < events.size(); t++) {
        count += events[t].second;
        exact[count] += events[t + 1].first - events[t].first;  // the gap up to the next event has this count
    }
    vector<long long> atLeast(n + 2, 0);
    for (int k = n; k >= 1; k--) atLeast[k] = atLeast[k + 1] + exact[k];
    return atLeast;
}

// The largest number of intervals that share a point. Closed intervals [l, r]: a start comes before an end at equal positions.
int maxOverlap(const vector<pair<int, int>>& intervals, bool closed) {
    vector<array<int, 3>> events;  // (position, order at equal positions, change)
    for (auto [l, r] : intervals) events.push_back({l, closed ? 0 : 1, +1}), events.push_back({r, closed ? 1 : 0, -1});
    sort(events.begin(), events.end());
    int count = 0, best = 0;
    for (auto [position, order, change] : events) best = max(best, count += change);
    return best;
}
// snippet:end

int main() {
    auto show = [](const vector<pair<int, int>>& iv) {
        vector<long long> a = coveredAtLeast(iv);
        string s;
        for (size_t k = 1; k <= iv.size(); k++) s += (k > 1 ? " " : "") + to_string(a[k]);
        return s;
    };
    cout << "[1,5) [2,7) [6,8): points in at least 1, 2, 3 intervals = " << show({{1, 5}, {2, 7}, {6, 8}}) << '\n';
    cout << "[1,3) [3,5): most overlap " << maxOverlap({{1, 3}, {3, 5}}, false) << "; as closed [1,3] [3,5]: " << maxOverlap({{1, 3}, {3, 5}}, true) << '\n';
    cout << "[2,4) [2,4) [4,6): points in at least 1, 2, 3 intervals = " << show({{2, 4}, {2, 4}, {4, 6}}) << '\n';
    // Exhaustive check: every list of 0..4 half-open intervals inside positions 0..5, against marking every point.
    vector<pair<int, int>> all;
    for (int l = 0; l <= 5; l++)
        for (int r = l + 1; r <= 5; r++) all.push_back({l, r});
    int m = all.size();
    for (int len = 0; len <= 4; len++) {
        int total = 1;
        for (int i = 0; i < len; i++) total *= m;
        for (int code = 0; code < total; code++) {
            vector<pair<int, int>> iv;
            int c = code;
            for (int i = 0; i < len; i++) iv.push_back(all[c % m]), c /= m;
            vector<int> cover(6, 0);
            for (auto [l, r] : iv)
                for (int x = l; x < r; x++) cover[x]++;
            vector<long long> want(len + 2, 0);
            int best = 0;
            for (int x = 0; x < 5; x++) {
                best = max(best, cover[x]);
                for (int k = 1; k <= cover[x]; k++) want[k]++;
            }
            vector<long long> got = coveredAtLeast(iv);
            for (int k = 1; k <= len; k++)
                if (got[k] != want[k]) return 1;
            if (maxOverlap(iv, false) != best) return 1;
        }
    }
    // Closed intervals [l, r] with l <= r inside positions 0..4, against counting the intervals that contain each point.
    vector<pair<int, int>> closedAll;
    for (int l = 0; l <= 4; l++)
        for (int r = l; r <= 4; r++) closedAll.push_back({l, r});
    int mc = closedAll.size();
    for (int len = 0; len <= 3; len++) {
        int total = 1;
        for (int i = 0; i < len; i++) total *= mc;
        for (int code = 0; code < total; code++) {
            vector<pair<int, int>> iv;
            int c = code;
            for (int i = 0; i < len; i++) iv.push_back(closedAll[c % mc]), c /= mc;
            int best = 0;
            for (int x = 0; x <= 4; x++) {
                int here = 0;
                for (auto [l, r] : iv) here += l <= x && x <= r;
                best = max(best, here);
            }
            if (maxOverlap(iv, true) != best) return 1;
        }
    }
}
