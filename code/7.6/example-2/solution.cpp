#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1723 Graph Paths I. A directed graph of n <= 100 nodes; count the walks with exactly k edges (k up to 10^9) from the node 1 to the node n,
modulo 10^9 + 7.
Input: n, m and k, then m lines "a b" (an edge from a to b).
Output: the number of walks modulo 10^9 + 7.
*/

const long long MOD = 1000000007;
using Matrix = vector<vector<long long>>;
Matrix multiply(const Matrix& a, const Matrix& b, long long mod) {
    int n = a.size();
    Matrix c(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
    return c;
}
Matrix power(Matrix base, long long e, long long mod) {  // base^e: start from the identity, then repeated squaring
    int n = base.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1 % mod;
    for (; e > 0; e >>= 1, base = multiply(base, base, mod))
        if (e & 1) result = multiply(result, base, mod);
    return result;
}

// snippet:begin
// Theorem 7.6.2: the entry (1, n) of the k-th power of the adjacency matrix (parallel edges count separately).
long long countWalksOfLength(int n, const vector<pair<int, int>>& edges, long long k) {
    Matrix adjacency(n, vector<long long>(n, 0));
    for (auto [a, b] : edges) adjacency[a - 1][b - 1]++;
    return power(adjacency, k, MOD)[0][n - 1];
}
// snippet:end

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) cin >> a >> b;
    cout << countWalksOfLength(n, edges, k) << "\n";
}
