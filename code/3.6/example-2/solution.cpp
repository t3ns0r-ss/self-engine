/*
Problem: AtCoder ABC 179 D, Leaping Tak. Cells 1..N; from cell i, jump to i + d for any d in the union S of K
disjoint segments [L, R], never past cell N. Count the ways to go from cell 1 to cell N, modulo 998244353.
Input: N K (N <= 2 * 10^5, K <= 10), then K lines L R.
Output: the count modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// ABC 179 D. ways[i] = the ways to reach cell i; the previous cell is i - d for d in a segment [lo, hi], a range of ways,
// summed with prefix sums.
long long leapingTak(int n, const vector<pair<int, int>>& seg) {
    const long long MOD = 998244353;
    vector<long long> ways(n + 1, 0), prefix(n + 2, 0);
    ways[1] = 1;
    prefix[2] = 1;
    for (int i = 2; i <= n; i++) {
        for (auto [lo, hi] : seg) {
            int from = max(1, i - hi), to = i - lo;
            if (to < 1) continue;
            ways[i] = (ways[i] + prefix[to + 1] - prefix[from] + MOD) % MOD;
        }
        prefix[i + 1] = (prefix[i] + ways[i]) % MOD;
    }
    return ways[n];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> seg(k);
    for (auto& [lo, hi] : seg) cin >> lo >> hi;
    cout << leapingTak(n, seg) << "\n";
}
