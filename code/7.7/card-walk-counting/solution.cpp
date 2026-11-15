#include <bits/stdc++.h>
using namespace std;

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

long long matrixWalks(const Matrix& a, int from, int to, int len) { return power(a, len, MOD)[from][to]; }
long long dfsWalks(const Matrix& a, int from, int to, int len) {
    if (len == 0) return from == to;
    long long total = 0;
    for (size_t next = 0; next < a.size(); next++) total += a[from][next] * dfsWalks(a, next, to, len - 1);
    return total;
}
// simple paths (no repeated vertex) with len edges from `from` to `to`
long long simplePaths(const Matrix& a, int at, int to, int len, int used) {
    if (len == 0) return at == to;
    long long total = 0;
    for (size_t next = 0; next < a.size(); next++)
        if (a[at][next] && !(used >> next & 1)) total += simplePaths(a, next, to, len - 1, used | 1 << next);
    return total;
}
int main() {
    // P1: edges 0->1, 1->2, 2->0, 0->2: walks of length 5 from 0 to 2
    Matrix g = {{0, 1, 1}, {0, 0, 1}, {1, 0, 0}};
    cout << "P1 brute=" << dfsWalks(g, 0, 2, 5) << " method=" << matrixWalks(g, 0, 2, 5) << "\n";
    // P2: binary strings of length 6 without two adjacent ones: walks of length 6 in the automaton (last bit 0 or 1), counted from the state 0
    Matrix automaton = {{1, 1}, {1, 0}};
    long long strings = 0;
    for (int mask = 0; mask < 64; mask++)
        if (!(mask & (mask >> 1))) strings++;
    long long viaMatrix = (matrixWalks(automaton, 0, 0, 6) + matrixWalks(automaton, 0, 1, 6)) % MOD;
    cout << "P2 brute=" << strings << " method=" << viaMatrix << "\n";
    // N1: K4, paths with 3 edges from 0 to 1 that do not repeat a vertex, against the walks of length 3
    Matrix k4(4, vector<long long>(4, 1));
    for (int i = 0; i < 4; i++) k4[i][i] = 0;
    cout << "N1 brute=" << simplePaths(k4, 0, 1, 3, 1) << " method=" << matrixWalks(k4, 0, 1, 3) << "\n";
}
