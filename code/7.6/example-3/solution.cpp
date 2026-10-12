#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1724 Graph Paths II. A directed graph of n <= 100 nodes with edge weights up to 10^9; the least total weight of a walk with exactly
k edges (k up to 10^9) from the node 1 to the node n, or -1.
Input: n, m and k, then m lines "a b c" (an edge from a to b of weight c).
Output: the least weight, or -1.
*/

using Matrix = vector<vector<long long>>;
const long long INF = (long long)2e18;
Matrix minPlusMultiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix c(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                if (a[i][k] < INF && b[k][j] < INF) c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    return c;
}
Matrix minPlusPower(Matrix base, long long e) {
    int n = base.size();
    Matrix result(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) result[i][i] = 0;
    for (; e > 0; e >>= 1, base = minPlusMultiply(base, base))
        if (e & 1) result = minPlusMultiply(result, base);
    return result;
}

// snippet:begin
// Theorem 7.6.4 over (min, +): the entry (1, n) of weights^k; a parallel edge keeps the smaller weight. A walk has at most 10^9 edges of weight 10^9, so
// its weight is at most 10^18, below INF.
long long cheapestWalk(int n, const vector<array<long long, 3>>& edges, long long k) {
    Matrix weights(n, vector<long long>(n, INF));
    for (auto [a, b, c] : edges) weights[a - 1][b - 1] = min(weights[a - 1][b - 1], c);
    long long d = minPlusPower(weights, k)[0][n - 1];
    return d < INF ? d : -1;
}
// snippet:end

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<array<long long, 3>> edges(m);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    cout << cheapestWalk(n, edges, k) << "\n";
}
