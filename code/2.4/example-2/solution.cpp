/*
Problem: AtCoder ABC 127 E, Cell Distance.
Input: N M K (2 <= N*M <= 2*10^5, 2 <= K <= N*M).
Output: the sum over all ways to choose K of the N*M cells of the sum of Manhattan distances
between the chosen cells, modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long power(long long a, long long b) {
    long long r = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    long long cells = n * m;
    vector<long long> fact(cells + 1, 1);
    for (long long i = 1; i <= cells; i++) fact[i] = fact[i - 1] * i % MOD;
    // each pair of cells is in C(cells - 2, k - 2) of the arrangements (Theorem 2.4.3)
    long long ways = fact[cells - 2] * power(fact[k - 2], MOD - 2) % MOD * power(fact[cells - k], MOD - 2) % MOD;
    long long pairDist = 0;  // sum of |dx| + |dy| over all unordered pairs of cells
    for (long long d = 1; d < n; d++)  // row difference d: (n - d) pairs of rows, m * m column choices
        pairDist = (pairDist + d * (n - d) % MOD * (m * m % MOD)) % MOD;
    for (long long d = 1; d < m; d++)
        pairDist = (pairDist + d * (m - d) % MOD * (n * n % MOD)) % MOD;
    cout << pairDist * ways % MOD << "\n";
}
