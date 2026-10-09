/*
Problem: n cities with one-way travel times d[i][j]. Starting at city 0, visit every city exactly once and
return to city 0 in the least total time.
Input: n (1 <= n <= 16), then the n x n matrix d (0 <= d[i][j] <= 10^9, d[i][i] = 0).
Output: the least total time (0 if n = 1).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> d(n, vector<long long>(n));
    for (auto& row : d)
        for (auto& x : row) cin >> x;
    const long long INF = LLONG_MAX / 4;
    // dp[mask][v] = shortest path from 0 visiting exactly mask and ending at v (Theorem 3.7.2)
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask += 2) {      // masks that contain city 0
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] >= INF) continue;
            for (int u = 0; u < n; u++)
                if (!(mask >> u & 1))
                    dp[mask | 1 << u][u] = min(dp[mask | 1 << u][u], dp[mask][v] + d[v][u]);
        }
    }
    long long best = (n == 1) ? 0 : INF;
    for (int v = 1; v < n; v++) best = min(best, dp[(1 << n) - 1][v] + d[v][0]);  // close the tour
    cout << best << "\n";
}
