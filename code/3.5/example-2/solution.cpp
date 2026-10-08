/*
Problem: AtCoder ABC 179 D, Leaping Tak. Cells 1..N; from cell i, jump to i + d for any d in the union S of K
disjoint segments [L, R], never past cell N. Count the ways to go from cell 1 to cell N, modulo 998244353.
Input: N K (N <= 2 * 10^5, K <= 10), then K lines L R.
Output: the count modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> lo(k), hi(k);
    for (int s = 0; s < k; s++) cin >> lo[s] >> hi[s];
    // ways[i] = ways to reach cell i; prefix[i] = ways[1] + ... + ways[i - 1]
    vector<long long> ways(n + 1, 0), prefix(n + 2, 0);
    ways[1] = 1;
    prefix[2] = 1;
    for (int i = 2; i <= n; i++) {
        for (int s = 0; s < k; s++) {
            // the previous cell is i - d for d in [lo, hi]: the cells [i - hi, i - lo], clipped at 1
            int from = max(1, i - hi[s]), to = i - lo[s];
            if (to < 1) continue;
            ways[i] = (ways[i] + prefix[to + 1] - prefix[from] + MOD) % MOD;
        }
        prefix[i + 1] = (prefix[i] + ways[i]) % MOD;
    }
    cout << ways[n] << "\n";
}
