/*
Problem: choose exactly k elements of an array, no two of them adjacent, with the largest possible sum.
Input: n k (1 <= n <= 2000, 1 <= k <= n), then n integers (|a_i| <= 10^9).
Output: the largest sum, or "impossible" if no such choice exists.
*/
#include <bits/stdc++.h>
using namespace std;

const long long NONE = LLONG_MIN;  // marks a state that no valid choice reaches

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    // dp[i][j] = best sum choosing exactly j of the first i elements, no two adjacent (Theorem 3.2.3)
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, NONE));
    dp[0][0] = 0;  // base case: nothing chosen yet
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j];  // element i not chosen
            // element i chosen: element i - 1 is not, so come from the first max(i - 2, 0) elements
            if (j > 0 && dp[max(i - 2, 0)][j - 1] != NONE)
                dp[i][j] = max(dp[i][j], dp[max(i - 2, 0)][j - 1] + a[i]);
        }
    if (dp[n][k] == NONE) cout << "impossible\n";
    else cout << dp[n][k] << "\n";
}
