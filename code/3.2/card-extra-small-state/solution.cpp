#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: two days with points 10 1 1 on both days, never the same activity twice in a row. Brute: all pairs. Method: dp[day][last].
    vector<vector<int>> p = {{10, 1, 1}, {10, 1, 1}};
    int brute = 0;
    for (int a = 0; a < 3; a++) for (int b = 0; b < 3; b++) if (a != b) brute = max(brute, p[0][a] + p[1][b]);
    vector<vector<int>> dp(2, vector<int>(3));
    for (int j = 0; j < 3; j++) dp[0][j] = p[0][j];
    for (int j = 0; j < 3; j++) { int bp = 0; for (int q = 0; q < 3; q++) if (q != j) bp = max(bp, dp[0][q]); dp[1][j] = bp + p[1][j]; }
    cout << "P1 brute=" << brute << " method=" << *max_element(dp[1].begin(), dp[1].end()) << '\n';
    // N1: the largest value with capacity 10^9 over 3 items; the table dp[item][capacity] has 4 * 10^9 states.
    long long cap = 1000000000;
    vector<array<long long, 2>> items = {{600000000, 5}, {500000000, 4}, {400000000, 3}};  // {weight, value}
    long long bruteV = 0;
    for (int mask = 0; mask < 8; mask++) {
        long long w = 0, v = 0;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) w += items[i][0], v += items[i][1];
        if (w <= cap) bruteV = max(bruteV, v);
    }
    long long states = 4 * (cap + 1);
    cout << "N1 brute=" << bruteV << " method=" << (states > 100000000LL ? "too-slow" : "ok") << '\n';
}
