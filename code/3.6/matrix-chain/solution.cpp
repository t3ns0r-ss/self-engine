/*
Problem: n matrices are multiplied in the given order; matrix i has size d[i-1] x d[i]. Multiplying a p x q matrix
by a q x r matrix costs p * q * r. Choose the bracketing that minimises the total cost.
Input: n (1 <= n <= 300), then d[0..n] (1 <= d[i] <= 100).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> d(n + 1);
    for (auto& x : d) cin >> x;
    // best[l][r] = cheapest way to multiply matrices l..r (1-based) into one
    vector<vector<long long>> best(n + 2, vector<long long>(n + 2, 0));
    for (int len = 2; len <= n; len++) {          // shorter segments first (Theorem 3.6.1)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            best[l][r] = LLONG_MAX;
            for (int k = l; k < r; k++) {         // the last multiplication joins [l, k] and [k + 1, r]
                long long cost = best[l][k] + best[k + 1][r] + d[l - 1] * d[k] * d[r];
                best[l][r] = min(best[l][r], cost);
            }
        }
    }
    cout << best[1][n] << "\n";
}
