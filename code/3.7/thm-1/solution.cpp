#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.1. Assignment over masks: dp[mask] = the least cost of giving the first |mask| workers the jobs in mask; the last of
// them took some job j in mask. Returns the whole table.
vector<long long> assignmentTable(const vector<vector<long long>>& c) {
    int n = c.size();
    vector<long long> dp(1 << n, LLONG_MAX);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++)
        for (int j = 0; j < n; j++)
            if (mask >> j & 1) dp[mask] = min(dp[mask], dp[mask ^ 1 << j] + c[__builtin_popcount(mask) - 1][j]);
    return dp;
}
// snippet:end

int main() {
    vector<vector<long long>> c = {{4, 1, 3}, {2, 0, 5}, {3, 2, 2}};
    auto dp = assignmentTable(c);
    cout << "dp for the masks 000 .. 111:";
    for (long long x : dp) cout << ' ' << x;
    cout << "\nanswer " << dp[7] << '\n';
    mt19937 rng(61);
    for (int round = 0; round < 200; round++) {
        int n = 1 + rng() % 6;
        vector<vector<long long>> m(n, vector<long long>(n));
        for (auto& row : m) for (auto& x : row) x = rng() % 20;
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long best = LLONG_MAX;
        do {
            long long s = 0;
            for (int i = 0; i < n; i++) s += m[i][p[i]];
            best = min(best, s);
        } while (next_permutation(p.begin(), p.end()));
        if (assignmentTable(m)[(1 << n) - 1] != best) return 1;
    }
}
