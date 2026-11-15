#include <bits/stdc++.h>
using namespace std;

long long tour(const vector<vector<long long>>& d) {
    int n = d.size();
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask += 2) for (int v = 0; v < n; v++) {
        if (dp[mask][v] >= INF) continue;
        for (int u = 0; u < n; u++) if (!(mask >> u & 1)) dp[mask | 1 << u][u] = min(dp[mask | 1 << u][u], dp[mask][v] + d[v][u]);
    }
    long long best = (n == 1) ? 0 : INF;
    for (int v = 1; v < n; v++) best = min(best, dp[(1 << n) - 1][v] + d[v][0]);
    return best;
}
int main() {
    // P1: the four-city tour. Brute: all 3! orders after city 0. Method: dp over (visited set, last city).
    vector<vector<long long>> d = {{0, 2, 9, 10}, {1, 0, 6, 4}, {15, 7, 0, 8}, {6, 3, 12, 0}};
    vector<int> p = {1, 2, 3};
    long long best = LLONG_MAX;
    do { long long s = 0; int at = 0; for (int v : p) s += d[at][v], at = v; best = min(best, s + d[at][0]); } while (next_permutation(p.begin(), p.end()));
    cout << "P1 brute=" << best << " method=" << tour(d) << '\n';
    // N1: visit 100000 points on a number line; the best walk is max - min after sorting, the (set, last) table has 2^100000 states.
    mt19937 rng(7);
    vector<long long> x(100000);
    for (auto& v : x) v = rng() % 1000000000;
    long long walk = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
    cout << "N1 brute=" << walk << " method=" << (100000 > 18 ? "too-slow" : "ok") << '\n';
}
