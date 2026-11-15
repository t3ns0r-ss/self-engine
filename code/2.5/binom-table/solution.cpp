/*
Problem: answer q queries C(n, r) modulo 10^9 + 7.
Input: q (1 <= q <= 2*10^5), then q lines n r (0 <= n <= 10^6, 0 <= r <= 10^6).
Output: C(n, r) mod 10^9 + 7 for each query (0 when r > n).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
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
// Theorem 2.5.3. fact[i] = i! and inv[i] = (i!)^(-1) modulo the prime MOD, for i <= N < MOD; C(n, r) in O(1).
struct Binom {
    vector<long long> fact, inv;
    Binom(int N) : fact(N + 1, 1), inv(N + 1, 1) {
        for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
        inv[N] = power(fact[N], MOD - 2);                              // Fermat, once
        for (int i = N; i >= 1; i--) inv[i - 1] = inv[i] * i % MOD;    // (i-1)!^(-1) = i!^(-1) * i
    }
    long long C(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] * inv[r] % MOD * inv[n - r] % MOD;
    }
};
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Binom b(1000000);
    int q;
    cin >> q;
    while (q--) {
        int n, r;
        cin >> n >> r;
        cout << b.C(n, r) << "\n";
    }
}
