/*
Problem: AtCoder ABC 162 E, Sum of gcd of Tuples (Hard).
Input: N K (2 <= N <= 10^5, 1 <= K <= 10^5).
Output: the sum of gcd(A_1, ..., A_N) over all K^N sequences with 1 <= A_i <= K, modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The sum of gcd(A_1..A_N) over all K^N sequences, modulo 10^9 + 7: f[d] = sequences with gcd exactly d,
// from the (K/d)^N sequences of multiples of d minus those with gcd 2d, 3d, ... (Theorem 2.1.6).
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
long long sumGcdTuples(long long N, long long K) {
    vector<long long> f(K + 1, 0);
    long long ans = 0;
    for (long long d = K; d >= 1; d--) {
        f[d] = power(K / d, N);
        for (long long k = 2 * d; k <= K; k += d) f[d] = (f[d] - f[k] + MOD) % MOD;
        ans = (ans + d % MOD * f[d]) % MOD;
    }
    return ans;
}
// snippet:end

int main() {
    long long N, K;
    cin >> N >> K;
    cout << sumGcdTuples(N, K) << "\n";
}
