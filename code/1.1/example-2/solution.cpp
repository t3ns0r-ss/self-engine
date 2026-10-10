/*
Problem: ABC 221 D Online games. Player i logged in on days A_i .. A_i + B_i - 1. For each k = 1..N,
count the days on which exactly k players logged in.
Input: N (1 <= N <= 2*10^5), then N lines "A_i B_i" (1 <= A_i, B_i <= 10^9).
Output: D_1 .. D_N.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// days[k] = number of days with exactly k players, for players logged in on the half-open day ranges [a, a + b).
vector<long long> loginDays(const vector<pair<long long, long long>>& ab) {
    int n = ab.size();
    vector<pair<long long, int>> events;  // (day, change); days reach 2*10^9
    for (auto [a, b] : ab) {
        events.push_back({a, +1});
        events.push_back({a + b, -1});
    }
    sort(events.begin(), events.end());
    vector<long long> days(n + 1, 0);
    int cur = 0;
    for (int k = 0; k + 1 < (int)events.size(); k++) {
        cur += events[k].second;
        days[cur] += events[k + 1].first - events[k].first;  // cur players until the next event day
    }
    return days;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> ab(n);
    for (auto& p : ab) cin >> p.first >> p.second;
    vector<long long> days = loginDays(ab);
    for (int k = 1; k <= n; k++) cout << days[k] << (k < n ? ' ' : '\n');
}
