#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int& x : prices) cin >> x;
    const long long NEG = LLONG_MIN / 4;
    vector<long long> dp(n + 2, NEG);  // dp[h] = the best profit with h shares held
    dp[0] = 0;
    for (int p : prices) {
        vector<long long> next = dp;
        for (int h = 0; h <= n; h++) {
            if (dp[h] == NEG) continue;
            next[h + 1] = max(next[h + 1], dp[h] - p);
            if (h > 0) next[h - 1] = max(next[h - 1], dp[h] + p);
        }
        dp = next;
    }
    cout << dp[0] << "\n";
}
