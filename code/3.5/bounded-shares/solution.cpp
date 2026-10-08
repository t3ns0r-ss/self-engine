/*
Problem: K identical items are shared among n people; person i must get between lo_i and hi_i
items. Count the ways to share all K items, modulo 10^9 + 7.
Input: n K (1 <= n <= 100, 0 <= K <= 10^5), then n lines lo_i hi_i (0 <= lo_i <= hi_i <= K).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

int main() {
    int n, k;
    cin >> n >> k;
    // dp[j] = ways for the people so far to take j items in total
    vector<long long> dp(k + 1, 0), prefix(k + 2, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int lo, hi;
        cin >> lo >> hi;
        // prefix[x] = dp[0] + ... + dp[x - 1] for the previous people (Theorem 3.5.4)
        for (int j = 0; j <= k; j++) prefix[j + 1] = (prefix[j] + dp[j]) % MOD;
        for (int j = 0; j <= k; j++) {
            // person i takes t in [lo, hi], so the others took j - t in [j - hi, j - lo]
            int from = max(0, j - hi), to = j - lo;
            dp[j] = (to < 0) ? 0 : (prefix[to + 1] - prefix[from] + MOD) % MOD;
        }
    }
    cout << dp[k] << "\n";
}
