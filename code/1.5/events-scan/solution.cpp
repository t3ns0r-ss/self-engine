/*
Problem: n visits, visit i covers the whole seconds l_i .. r_i (both included) and has a weight w_i.
Print (1) the most visits that share a second, (2) the largest total weight of the visits that share a second,
and (3) for k = 1 .. n, how many seconds are covered by at least k visits.
Input: n (1 <= n <= 10^5), then n lines "l r w" (0 <= l <= r <= 10^9, 1 <= w <= 10^9).
Output: three lines. The second is below 10^14.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.6. Closed seconds [l, r] are the half-open [l, r + 1). One scan over the sorted events answers three questions.
struct Answer {
    long long mostVisits = 0;          // the most visits that share a second
    long long mostWeight = 0;          // the largest total weight of visits that share a second
    vector<long long> atLeast;         // atLeast[k] = seconds covered by at least k visits
};
Answer scanEvents(const vector<array<long long, 3>>& visits) {  // each visit is {l, r, w}
    int n = visits.size();
    vector<array<long long, 3>> events;  // {position, kind, weight}; kind 0 = end, 1 = start, so ends sort first
    for (auto [l, r, w] : visits) events.push_back({l, 1, w}), events.push_back({r + 1, 0, w});
    sort(events.begin(), events.end());
    Answer ans;
    vector<long long> exact(n + 1, 0);  // exact[c] = seconds covered by exactly c visits
    long long count = 0, weight = 0;
    for (size_t t = 0; t < events.size(); t++) {
        auto [position, kind, w] = events[t];
        count += kind ? 1 : -1, weight += kind ? w : -w;
        ans.mostVisits = max(ans.mostVisits, count), ans.mostWeight = max(ans.mostWeight, weight);
        if (t + 1 < events.size()) exact[count] += events[t + 1][0] - position;  // the gap up to the next event
    }
    ans.atLeast.assign(n + 2, 0);
    for (int k = n; k >= 1; k--) ans.atLeast[k] = ans.atLeast[k + 1] + exact[k];  // "at least" is a suffix sum
    return ans;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<long long, 3>> visits(n);
    for (auto& v : visits) cin >> v[0] >> v[1] >> v[2];
    Answer ans = scanEvents(visits);
    cout << ans.mostVisits << "\n" << ans.mostWeight << "\n";
    for (int k = 1; k <= n; k++) cout << ans.atLeast[k] << (k < n ? ' ' : '\n');
}
