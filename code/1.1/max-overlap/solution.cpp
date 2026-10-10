/*
Problem: n closed intervals [l_i, r_i] of integers. Print the largest number of intervals that
contain one common integer, and the number of integers contained in at least one interval.
Input: n (1 <= n <= 2*10^5), then n lines "l_i r_i" (0 <= l_i <= r_i <= 10^9).
Output: "maxOverlap coveredIntegers".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.6. For closed integer intervals [l, r]: the largest number covering one point, and how many integer
// points are covered at all. [l, r] is the half-open [l, r + 1).
pair<int, long long> maxOverlap(const vector<pair<long long, long long>>& iv) {
    vector<pair<long long, int>> events;  // (time, change)
    for (auto [l, r] : iv) {
        events.push_back({l, +1});
        events.push_back({r + 1, -1});
    }
    sort(events.begin(), events.end());  // at equal times -1 comes before +1
    int cur = 0, best = 0;
    long long covered = 0;
    for (int k = 0; k < (int)events.size(); k++) {
        cur += events[k].second;
        best = max(best, cur);
        if (cur > 0 && k + 1 < (int)events.size()) covered += events[k + 1].first - events[k].first;  // cur until the next event
    }
    return {best, covered};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> iv(n);
    for (auto& p : iv) cin >> p.first >> p.second;
    pair<int, long long> r = maxOverlap(iv);
    cout << r.first << " " << r.second << "\n";
}
