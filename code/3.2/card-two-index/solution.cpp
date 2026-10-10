#include <bits/stdc++.h>
using namespace std;

long long gridPaths(int rows, int cols) {
    vector<vector<long long>> dp(rows + 1, vector<long long>(cols + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= rows; i++) for (int j = 0; j <= cols; j++) {
        if (i > 0) dp[i][j] += dp[i - 1][j];
        if (j > 0) dp[i][j] += dp[i][j - 1];
    }
    return dp[rows][cols];
}
long long brutePaths(int i, int j) { return i < 0 || j < 0 ? 0 : (i == 0 && j == 0) ? 1 : brutePaths(i - 1, j) + brutePaths(i, j - 1); }
long long kNonAdjacent(const vector<long long>& a, int k) {
    const long long NONE = LLONG_MIN;
    int n = a.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, NONE));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= k; j++) {
        dp[i][j] = dp[i - 1][j];
        if (j > 0 && dp[max(i - 2, 0)][j - 1] != NONE) dp[i][j] = max(dp[i][j], dp[max(i - 2, 0)][j - 1] + a[i - 1]);
    }
    return dp[n][k];
}
int main() {
    // P1: the lattice paths to (2, 2). Brute: recursion. Method: dp[i][j]. P2: exactly 2 non-adjacent of 3 -1 4 1 with the best sum.
    cout << "P1 brute=" << brutePaths(2, 2) << " method=" << gridPaths(2, 2) << '\n';
    vector<long long> a = {3, -1, 4, 1};
    long long brute = LLONG_MIN;
    for (int i = 0; i < 4; i++) for (int j = i + 2; j < 4; j++) brute = max(brute, a[i] + a[j]);
    cout << "P2 brute=" << brute << " method=" << kNonAdjacent(a, 2) << '\n';
    // N1: the lattice paths in a 100000 x 100000 grid, modulo 10^9 + 7; the table has 10^10 states.
    const long long MOD = 1000000007;
    long long fact = 1, num = 1, den = 1;
    for (long long i = 1; i <= 200000; i++) { num = num * i % MOD; if (i <= 100000) den = den * i % MOD; }
    auto power = [&](long long b, long long e) { long long r = 1; b %= MOD; while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; } return r; };
    long long answer = num * power(den, MOD - 2) % MOD * power(den, MOD - 2) % MOD;
    long long states = 100001LL * 100001LL;
    (void)fact;
    cout << "N1 brute=" << answer << " method=" << (states > 100000000LL ? "too-slow" : "ok") << '\n';
}
