/*
Problem: n closed intervals [l_i, r_i] of integers. Print the largest number of intervals that
contain one common integer, and the number of integers contained in at least one interval.
Input: n (1 <= n <= 2*10^5), then n lines "l_i r_i" (0 <= l_i <= r_i <= 10^9).
Output: "maxOverlap coveredIntegers".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, int>> events;  // (time, change)
    for (int i = 0; i < n; i++) {
        long long l, r;
        cin >> l >> r;
        events.push_back({l, +1});
        events.push_back({r + 1, -1});  // [l, r] of integers is the half-open [l, r + 1)
    }
    sort(events.begin(), events.end());  // at equal times -1 comes before +1 (Theorem 1.1.6)
    int cur = 0, best = 0;
    long long covered = 0;  // up to 10^9 + 1 integers
    for (int k = 0; k < (int)events.size(); k++) {
        cur += events[k].second;
        best = max(best, cur);
        // the count stays cur from this event to the next one (Theorem 1.1.6, part 3)
        if (cur > 0 && k + 1 < (int)events.size()) covered += events[k + 1].first - events[k].first;
    }
    cout << best << " " << covered << "\n";
}
