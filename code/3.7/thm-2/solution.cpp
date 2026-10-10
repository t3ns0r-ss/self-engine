#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.2. Paths through every vertex: dp[mask][v] = the shortest path from city 0 visiting exactly mask and ending at v;
// close the tour with the edge back to 0.
long long tour(const vector<vector<long long>>& d) {
    int n = d.size();
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask += 2)
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] >= INF) continue;
            for (int u = 0; u < n; u++)
                if (!(mask >> u & 1)) dp[mask | 1 << u][u] = min(dp[mask | 1 << u][u], dp[mask][v] + d[v][u]);
        }
    long long best = (n == 1) ? 0 : INF;
    for (int v = 1; v < n; v++) best = min(best, dp[(1 << n) - 1][v] + d[v][0]);
    return best;
}
// snippet:end

int main() {
    vector<vector<long long>> d = {{0, 2, 9, 10}, {1, 0, 6, 4}, {15, 7, 0, 8}, {6, 3, 12, 0}};
    cout << "shortest tour of the four cities: " << tour(d) << '\n';
    mt19937 rng(62);
    for (int round = 0; round < 200; round++) {
        int n = 1 + rng() % 7;
        vector<vector<long long>> m(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j) m[i][j] = 1 + rng() % 20;
        vector<int> p(n - 1);
        iota(p.begin(), p.end(), 1);
        long long best = LLONG_MAX;
        do {
            long long s = 0;
            int at = 0;
            for (int v : p) s += m[at][v], at = v;
            s += m[at][0];
            best = min(best, s);
        } while (next_permutation(p.begin(), p.end()));
        if (n == 1) best = 0;
        if (tour(m) != best) return 1;
    }
}
