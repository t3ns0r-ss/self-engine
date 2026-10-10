/*
Problem: K identical items are shared among n people; person i must get between lo_i and hi_i
items. Count the ways to share all K items, modulo 10^9 + 7.
Input: n K (1 <= n <= 100, 0 <= K <= 10^5), then n lines lo_i hi_i (0 <= lo_i <= hi_i <= K).
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.4. dp[j] = the ways for the people so far to take j items in total; person i takes t in [lo, hi], so the others
// took j - t in [j - hi, j - lo], a range of the previous row, summed with prefix sums.
long long boundedShares(int k, const vector<pair<int, int>>& limits) {
    const long long MOD = 1'000'000'007;
    vector<long long> dp(k + 1, 0), prefix(k + 2, 0);
    dp[0] = 1;
    for (auto [lo, hi] : limits) {
        for (int j = 0; j <= k; j++) prefix[j + 1] = (prefix[j] + dp[j]) % MOD;
        for (int j = 0; j <= k; j++) {
            int from = max(0, j - hi), to = j - lo;
            dp[j] = (to < 0) ? 0 : (prefix[to + 1] - prefix[from] + MOD) % MOD;
        }
    }
    return dp[k];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> limits(n);
    for (auto& [lo, hi] : limits) cin >> lo >> hi;
    cout << boundedShares(k, limits) << "\n";
}
