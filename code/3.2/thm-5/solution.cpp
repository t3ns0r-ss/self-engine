#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.5. Adding a small fact to the state: dp[i][j] = the best total of days 0..i with activity j on day i,
// when the same activity may not be chosen on two consecutive days.
long long noRepeat(const vector<vector<long long>>& p) {
    int n = p.size(), m = p[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m, 0));
    for (int j = 0; j < m; j++) dp[0][j] = p[0][j];
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++) {
            long long bestPrev = 0;
            for (int q = 0; q < m; q++) if (q != j) bestPrev = max(bestPrev, dp[i - 1][q]);
            dp[i][j] = bestPrev + p[i][j];
        }
    return *max_element(dp[n - 1].begin(), dp[n - 1].end());
}
// snippet:end

long long brute(const vector<vector<long long>>& p, int i = 0, int last = -1) {
    if (i == (int)p.size()) return 0;
    long long r = 0;
    for (int j = 0; j < (int)p[0].size(); j++) if (j != last) r = max(r, p[i][j] + brute(p, i + 1, j));
    return r;
}
int main() {
    vector<vector<long long>> p = {{10, 1, 1}, {10, 1, 1}};
    cout << "two days with points 10 1 1 on both: " << noRepeat(p) << " (the day alone as the state would give 20)\n";
    mt19937 rng(6);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 6, m = 2 + rng() % 3;
        vector<vector<long long>> q(n, vector<long long>(m));
        for (auto& row : q) for (auto& x : row) x = rng() % 10;
        if (noRepeat(q) != brute(q)) return 1;
    }
}
