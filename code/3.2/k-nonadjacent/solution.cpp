/*
Problem: choose exactly k elements of an array, no two of them adjacent, with the largest possible sum.
Input: n k (1 <= n <= 2000, 1 <= k <= n), then n integers (|a_i| <= 10^9).
Output: the largest sum, or "impossible" if no such choice exists.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.3. dp[i][j] = the best sum choosing exactly j of the first i elements, no two adjacent. NONE marks a state
// that no valid choice reaches.
const long long NONE = LLONG_MIN;
long long kNonAdjacent(const vector<long long>& a1, int k) {  // a1 is 1-based: a1[0] is unused
    int n = a1.size() - 1;
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, NONE));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j];  // element i not chosen
            if (j > 0 && dp[max(i - 2, 0)][j - 1] != NONE)
                dp[i][j] = max(dp[i][j], dp[max(i - 2, 0)][j - 1] + a1[i]);  // chosen: i - 1 is not
        }
    return dp[n][k];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long r = kNonAdjacent(a, k);
    if (r == NONE) cout << "impossible\n";
    else cout << r << "\n";
}
