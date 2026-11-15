#include <bits/stdc++.h>
using namespace std;

/*
Problem (Codeforces 797E, Array Queries): n numbers a_p (1 <= a_p <= n) and q questions (p, k): start at p and repeat p = p + a_p + k
until p > n; print the number of repetitions (1-based p).
Input: n, the n numbers, q, then q lines p k.
Output: the answer to each question on its own line.
*/

// snippet:begin
// A step k >= B leaves the array after at most n / B jumps, so it is simulated. For the steps k < B a table is filled from the right:
// dp[k][p] = 1 + dp[k][p + a[p] + k], or 1 if that position is past the end (0-based p).
struct Jumps {
    int n, B;
    vector<int> a;
    vector<vector<int>> dp;
    Jumps(const vector<int>& v, int threshold) : n(v.size()), B(threshold), a(v), dp(threshold) {
        for (int k = 1; k < B; k++) {
            dp[k].assign(n, 0);
            for (int p = n - 1; p >= 0; p--) {
                int next = p + a[p] + k;
                dp[k][p] = 1 + (next < n ? dp[k][next] : 0);
            }
        }
    }
    int query(int p, int k) const {
        if (k < B) return dp[k][p];
        int steps = 0;
        for (; p < n; p += a[p] + k) steps++;
        return steps;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    Jumps jumps(a, max(1, (int)sqrt((double)n)));
    cin >> q;
    while (q--) {
        int p, k;
        cin >> p >> k;
        cout << jumps.query(p - 1, k) << "\n";
    }
}
