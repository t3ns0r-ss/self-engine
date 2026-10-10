/*
Problem: where to hold the meeting.
Input: n m, then m lines "a b w": a two-way road of length w (1 <= w <= 10^9) between towns a and b (roads may repeat).
Output: the number of the town with the smallest total distance to all towns (the smallest number if several),
and that total; only towns from which every town can be reached count. Print "-1" if there is no such town.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.4. The town with the smallest total distance to all towns; d is the n+1 by n+1 matrix of road lengths
// (INF where no road, 0 on the diagonal). Returns {town, total}, or {-1, 0} when no town reaches all.
pair<int, long long> meetingTown(vector<vector<long long>> d) {
    const long long INF = LLONG_MAX / 4;
    int n = d.size() - 1;
    for (int k = 1; k <= n; k++)            // the middle town of the route goes in the OUTER loop
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
    pair<int, long long> best = {-1, 0};
    for (int i = 1; i <= n; i++) {
        long long total = 0;
        bool reachesAll = true;
        for (int j = 1; j <= n; j++) {
            if (d[i][j] >= INF) reachesAll = false;  // no road at all to town j
            else total += d[i][j];
        }
        if (reachesAll && (best.first == -1 || total < best.second)) best = {i, total};
    }
    return best;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        d[a][b] = min(d[a][b], w);
        d[b][a] = min(d[b][a], w);
    }
    auto [town, total] = meetingTown(d);
    if (town == -1) cout << -1 << "\n";
    else cout << town << " " << total << "\n";
}
