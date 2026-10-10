#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.3. Tables of i! and (i!)^(-1) modulo a prime MOD > N give C(n, r) in O(1).
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
    Binom b(2000);
    cout << "C(5, 2) = " << b.C(5, 2) << ", C(2000, 1000) = " << b.C(2000, 1000) << " (modulo 10^9 + 7)\n";
    vector<vector<long long>> P(201, vector<long long>(201, 0));
    for (int n = 0; n <= 200; n++) {
        P[n][0] = 1;
        for (int r = 1; r <= n; r++) P[n][r] = (P[n - 1][r - 1] + P[n - 1][r]) % MOD;
    }
    for (int n = 0; n <= 200; n++) for (int r = -2; r <= n + 2; r++) {
        long long want = (r < 0 || r > n) ? 0 : P[n][r];
        if (b.C(n, r) != want) return 1;
    }
}
