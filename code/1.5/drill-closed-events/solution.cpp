/*
Drill (about 5 minutes). n guests, guest i is in the hall during the whole days l_i .. r_i (both included).
Print the largest number of guests in the hall on one day. A guest who leaves on day 5 and one who arrives on day 5
are both there on day 5.
Input: n, then n lines "l r" (1 <= l <= r <= 10^9), n <= 2*10^5.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Closed days [l, r] are the half-open [l, r + 1). A guest then leaves at r + 1, and at equal times the
// leaving events come first (-1 sorts before +1), so no day is counted twice.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, int>> events;  // {time, +1 arrives / -1 leaves}
    for (int i = 0; i < n; i++) {
        long long l, r;
        cin >> l >> r;
        events.push_back({l, +1});
        events.push_back({r + 1, -1});
    }
    sort(events.begin(), events.end());
    int inside = 0, best = 0;
    for (auto [time, delta] : events) {
        inside += delta;
        best = max(best, inside);
    }
    cout << best << "\n";
}
// snippet:end
