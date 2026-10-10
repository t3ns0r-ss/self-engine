/*
Problem: split n items with weights w_i into groups of total weight at most C each; a group scores the square
of its total weight. Maximise the total score.
Input: n C (1 <= n <= 16, 1 <= C <= 10^4), then w_1..w_n (1 <= w_i <= C).
Output: the largest total score.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.4. dp[mask] = the best score for splitting mask into groups of total weight at most cap, a group scoring the square
// of its total: choose the group of the lowest item among the submasks of mask.
long long bestPartition(const vector<long long>& w, long long cap) {
    int n = w.size(), full = (1 << n) - 1;
    vector<long long> sum(1 << n, 0), dp(1 << n, -1);
    for (int mask = 1; mask <= full; mask++) {
        int low = __builtin_ctz(mask);
        sum[mask] = sum[mask ^ 1 << low] + w[low];
    }
    dp[0] = 0;
    for (int mask = 1; mask <= full; mask++) {
        int low = mask & -mask;  // the group of the lowest item is chosen first
        for (int s = mask; s > 0; s = (s - 1) & mask) {
            if (!(s & low) || sum[s] > cap) continue;
            dp[mask] = max(dp[mask], dp[mask ^ s] + sum[s] * sum[s]);
        }
    }
    return dp[full];
}
// snippet:end

int main() {
    int n;
    long long cap;
    cin >> n >> cap;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    cout << bestPartition(w, cap) << "\n";
}
