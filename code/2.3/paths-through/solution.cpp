/*
Problem: lattice paths from (0, 0) to (a, b) with unit steps right and up.
Input: a b (0 <= a, b <= 10^6), q (1 <= q <= 2*10^5), then q lines x y (0 <= x, y <= 10^6).
Output: the total number of paths, then for each query the number of paths through (x, y), all modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
vector<long long> fact, inv;

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

long long paths(long long dx, long long dy) {  // C(dx + dy, dx)  (Theorem 2.3.7)
    if (dx < 0 || dy < 0) return 0;
    return fact[dx + dy] * inv[dx] % MOD * inv[dy] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b;
    int q;
    cin >> a >> b >> q;
    int N = a + b;
    fact.assign(N + 1, 1);
    inv.assign(N + 1, 1);
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N] = power(fact[N], MOD - 2);
    for (int i = N; i >= 1; i--) inv[i - 1] = inv[i] * i % MOD;
    cout << paths(a, b) << "\n";
    while (q--) {
        long long x, y;
        cin >> x >> y;
        cout << paths(x, y) * paths(a - x, b - y) % MOD << "\n";  // first half, then second half
    }
}
