#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed graph of n <= 64 vertices; is there a walk with exactly L edges (L up to 10^18) from the vertex s to the vertex t?
Input: n, m and L, then m lines "a b" (an edge from a to b, vertices from 0), then s and t.
Output: yes or no.
*/

// snippet:begin
// Theorem 7.6.4 over the semiring (or, and): a row of the matrix is a 64-bit mask of the columns that are true. The product of a and b has
// as row i the OR of the rows k of b for which the bit k of the row i of a is set. The identity has the bit i in the row i.
using BoolMatrix = vector<unsigned long long>;
BoolMatrix boolMultiply(const BoolMatrix& a, const BoolMatrix& b) {
    BoolMatrix c(a.size(), 0);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t k = 0; k < b.size(); k++)
            if (a[i] >> k & 1) c[i] |= b[k];
    return c;
}
bool walkExists(int n, const vector<pair<int, int>>& edges, long long length, int from, int to) {
    BoolMatrix base(n, 0), result(n, 0);
    for (int i = 0; i < n; i++) result[i] = 1ULL << i;
    for (auto [a, b] : edges) base[a] |= 1ULL << b;
    for (; length > 0; length >>= 1, base = boolMultiply(base, base))
        if (length & 1) result = boolMultiply(result, base);
    return result[from] >> to & 1;
}
// snippet:end

int main() {
    int n, m, from, to;
    long long length;
    cin >> n >> m >> length;
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) cin >> a >> b;
    cin >> from >> to;
    cout << (walkExists(n, edges, length, from, to) ? "yes" : "no") << "\n";
}
