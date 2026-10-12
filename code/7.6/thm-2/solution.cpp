#include <bits/stdc++.h>
using namespace std;

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
// Theorem 7.6.2. adjacency[i][j] = the number of edges from i to j. The number of walks with exactly `length` edges from `from` to `to`
// is the entry (from, to) of adjacency^length (power is the function of Theorem 7.6.1).
long long countWalks(const Matrix& adjacency, int from, int to, long long length, long long mod) {
    return power(adjacency, length, mod)[from][to];
}
// snippet:end

long long bruteWalks(const Matrix& adjacency, int from, int to, int length) {  // follows every edge, one step at a time
    if (length == 0) return from == to;
    long long total = 0;
    for (size_t next = 0; next < adjacency.size(); next++)
        for (long long copy = 0; copy < adjacency[from][next]; copy++) total += bruteWalks(adjacency, next, to, length - 1);
    return total;
}

int main() {
    const long long MOD = 1000000007;
    Matrix triangle = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    cout << "triangle, walks of length 3 from 0 to 0: " << countWalks(triangle, 0, 0, 3, MOD) << "\n";
    cout << "triangle, walks of length 3 from 0 to 1: " << countWalks(triangle, 0, 1, 3, MOD) << "\n";
    Matrix path = {{0, 1, 0}, {0, 0, 1}, {0, 0, 1}};
    cout << "path 0 -> 1 -> 2 with a loop at 2, walks of length 4 from 0 to 2: " << countWalks(path, 0, 2, 4, MOD) << "\n";
    // Check (not printed): 300 random graphs of 4 vertices with up to 2 parallel edges, all pairs, lengths 0 to 6.
    mt19937 rng(7);
    for (int round = 0; round < 300; round++) {
        Matrix a(4, vector<long long>(4));
        for (auto& row : a)
            for (auto& x : row) x = rng() % 3;
        for (int len = 0; len <= 6; len++)
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (countWalks(a, i, j, len, MOD) != bruteWalks(a, i, j, len)) return 1;
    }
}
