/*
Problem: n workers and n jobs; c[i][j] is the cost of giving job j to worker i. Give every worker one job,
every job to one worker, at the least total cost.
Input: n (1 <= n <= 20), then the n x n matrix c (0 <= c[i][j] <= 10^9).
Output: the least total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.1. dp[mask] = the least cost for workers 0..|mask|-1 to take exactly the jobs in mask; the next worker is |mask|.
long long assignment(const vector<vector<long long>>& c) {
    int n = c.size();
    vector<long long> dp(1 << n, LLONG_MAX);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == LLONG_MAX) continue;
        int worker = __builtin_popcount(mask);  // the next worker to place
        if (worker == n) continue;
        for (int j = 0; j < n; j++)
            if (!(mask >> j & 1)) dp[mask | 1 << j] = min(dp[mask | 1 << j], dp[mask] + c[worker][j]);
    }
    return dp[(1 << n) - 1];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> c(n, vector<long long>(n));
    for (auto& row : c)
        for (auto& x : row) cin >> x;
    cout << assignment(c) << "\n";
}
