/*
Problem: ABC 221 D Online games. Player i logged in on days A_i .. A_i + B_i - 1. For each k = 1..N,
count the days on which exactly k players logged in.
Input: N (1 <= N <= 2*10^5), then N lines "A_i B_i" (1 <= A_i, B_i <= 10^9).
Output: D_1 .. D_N.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, int>> events;  // (day, change); days reach 2*10^9
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        events.push_back({a, +1});
        events.push_back({a + b, -1});  // logged in on [a, a + b), half-open
    }
    sort(events.begin(), events.end());
    vector<long long> days(n + 1, 0);  // days[k]: days with exactly k players; up to 2*10^9
    int cur = 0;
    for (int k = 0; k + 1 < (int)events.size(); k++) {
        cur += events[k].second;
        // cur players on every day from this event's day up to the next event's day (exclusive)
        days[cur] += events[k + 1].first - events[k].first;
    }
    for (int k = 1; k <= n; k++) cout << days[k] << (k < n ? ' ' : '\n');
}
