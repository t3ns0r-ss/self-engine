#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n), P(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        P[i + 1] = P[i] + a[i];
    }
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
    dp[0][0] = 0;
    for (int t = 1; t <= k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[t - 1][j] < INF) dp[t][i] = min(dp[t][i], dp[t - 1][j] + (P[i] - P[j]) * (P[i] - P[j]));
    cout << dp[k][n] << "\n";
}
