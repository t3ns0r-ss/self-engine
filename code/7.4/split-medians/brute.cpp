#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    for (long long& v : x) cin >> v;
    const long long INF = LLONG_MAX / 4;
    // cost of the houses j..i-1 (0-based, half open): try every mailbox house
    auto group = [&](int j, int i) {
        long long best = INF;
        for (int m = j; m < i; m++) {
            long long s = 0;
            for (int t = j; t < i; t++) s += llabs(x[t] - x[m]);
            best = min(best, s);
        }
        return best;
    };
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
    dp[0][0] = 0;
    for (int t = 1; t <= k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[t - 1][j] < INF) dp[t][i] = min(dp[t][i], dp[t - 1][j] + group(j, i));
    cout << dp[k][n] << "\n";
}
