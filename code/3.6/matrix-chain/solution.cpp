/*
Problem: n matrices are multiplied in the given order; matrix i has size d[i-1] x d[i]. Multiplying a p x q matrix
by a q x r matrix costs p * q * r. Choose the bracketing that minimises the total cost.
Input: n (1 <= n <= 300), then d[0..n] (1 <= d[i] <= 100).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.2. best[l][r] = the cheapest way to multiply matrices l..r (matrix i is d[i-1] x d[i]); the last multiplication
// joins [l, k] and [k + 1, r]. Segments are filled by increasing length (Theorem 3.6.1).
long long matrixChain(const vector<long long>& d) {
    int n = d.size() - 1;
    vector<vector<long long>> best(n + 2, vector<long long>(n + 2, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            best[l][r] = LLONG_MAX;
            for (int k = l; k < r; k++)
                best[l][r] = min(best[l][r], best[l][k] + best[k + 1][r] + d[l - 1] * d[k] * d[r]);
        }
    return best[1][n];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> d(n + 1);
    for (auto& x : d) cin >> x;
    cout << matrixChain(d) << "\n";
}
