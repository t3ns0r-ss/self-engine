/*
Problem: on each of n days choose one of m activities; activity j on day i earns p[i][j] points, and the same
activity may not be chosen on two consecutive days. Print the largest total.
Input: n m (1 <= n <= 10^5, 2 <= m <= 10), then n lines of m integers (0 <= p[i][j] <= 10^4).
Output: the largest total.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> p(n, vector<long long>(m));
    for (auto& row : p)
        for (auto& x : row) cin >> x;
    // dp[i][j] = best total of days 0..i with activity j on day i: the state is (day, last activity) (Theorem 3.2.5)
    vector<vector<long long>> dp(n, vector<long long>(m, 0));
    for (int j = 0; j < m; j++) dp[0][j] = p[0][j];  // base cases
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++) {
            long long bestPrev = 0;
            for (int q = 0; q < m; q++)
                if (q != j) bestPrev = max(bestPrev, dp[i - 1][q]);  // any different activity yesterday
            dp[i][j] = bestPrev + p[i][j];
        }
    cout << *max_element(dp[n - 1].begin(), dp[n - 1].end()) << "\n";
}
