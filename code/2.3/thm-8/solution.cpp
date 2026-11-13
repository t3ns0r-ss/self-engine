#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.8 (Lucas). For a prime p, C(n, r) mod p is the product of C(n_i, r_i) over the base-p digits of n and r.
struct Lucas {
    int p;
    vector<long long> fact, inv;  // i! and (i!)^(-1) modulo p, only for 0 <= i < p
    long long power(long long a, long long b) const {
        long long r = 1 % p;
        for (a %= p; b > 0; b >>= 1, a = a * a % p) if (b & 1) r = r * a % p;
        return r;
    }
    Lucas(int p_) : p(p_), fact(p_, 1), inv(p_, 1) {
        for (int i = 1; i < p; i++) fact[i] = fact[i - 1] * i % p;
        inv[p - 1] = power(fact[p - 1], p - 2);                      // Fermat, once
        for (int i = p - 1; i >= 1; i--) inv[i - 1] = inv[i] * i % p;
    }
    long long digitC(int a, int b) const { return b > a ? 0 : fact[a] * inv[b] % p * inv[a - b] % p; }
    long long C(long long n, long long r) const {
        if (r < 0 || r > n) return 0;
        long long res = 1 % p;
        for (; n > 0 && res != 0; n /= p, r /= p) res = res * digitC(n % p, r % p) % p;
        return res;
    }
};
// snippet:end

int main() {
    // hand-checked values
    cout << "C(14, 7) mod 7 = " << Lucas(7).C(14, 7) << ", C(100, 51) mod 7 = " << Lucas(7).C(100, 51)
         << ", C(13, 4) mod 3 = " << Lucas(3).C(13, 4) << ", C(10, 3) mod 2 = " << Lucas(2).C(10, 3) << "\n";
    long long big = (1LL << 60) - 1;  // all ones in binary: every C(big, r) is odd
    cout << "C(2^60 - 1, 12345) mod 2 = " << Lucas(2).C(big, 12345) << ", C(2^60, 1) mod 2 = " << Lucas(2).C(1LL << 60, 1) << "\n";
    // every value against Pascal's triangle with the modulus applied at each step
    for (int p : {2, 3, 5, 7, 11, 13}) {
        Lucas L(p);
        vector<vector<int>> P(301, vector<int>(301, 0));
        for (int n = 0; n <= 300; n++) {
            P[n][0] = 1 % p;
            for (int r = 1; r <= n; r++) P[n][r] = (P[n - 1][r - 1] + P[n - 1][r]) % p;
        }
        for (int n = 0; n <= 300; n++) for (int r = -1; r <= n + 1; r++) {
            long long want = (r < 0 || r > n) ? 0 : P[n][r];
            if (L.C(n, r) != want) return 1;
        }
    }
}
