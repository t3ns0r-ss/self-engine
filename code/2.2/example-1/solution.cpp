/*
Problem: AtCoder ABC 162 E, Sum of gcd of Tuples (Hard).
Input: N K (2 <= N <= 10^5, 1 <= K <= 10^5).
Output: the sum of gcd(A_1, ..., A_N) over all K^N sequences with 1 <= A_i <= K, modulo 10^9 + 7.
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
    long long N, K;
    cin >> N >> K;
    vector<long long> f(K + 1, 0);  // f[d] = number of sequences with gcd exactly d
    long long ans = 0;
    for (long long d = K; d >= 1; d--) {
        f[d] = power(K / d, N);  // every A_i a multiple of d: (K/d)^N sequences
        for (long long k = 2 * d; k <= K; k += d) f[d] = (f[d] - f[k] + MOD) % MOD;  // Theorem 2.1.6
        ans = (ans + d % MOD * f[d]) % MOD;
    }
    cout << ans << "\n";
}
