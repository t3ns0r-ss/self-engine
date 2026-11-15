/*
Problem: LeetCode 1735, Count Ways to Make Array With Product (as standard input and output).
Input: q (1 <= q <= 10^4), then q lines n k (1 <= n, k <= 10^4).
Output: for each query, the number of arrays of n positive integers with product k, modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// LeetCode 1735. The arrays of n positive integers with product k: for each prime p^e of k, the e copies of p are
// spread over the n slots, C(e + n - 1, n - 1) ways (stars and bars); the primes multiply (product rule).
const long long MOD = 1000000007;
const int N = 10100;  // n + exponent - 1 < 10^4 + 14
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
long long productWays(int n, int k, const vector<long long>& fact, const vector<long long>& inv) {
    auto C = [&](int a, int b) { return fact[a] * inv[b] % MOD * inv[a - b] % MOD; };
    long long ways = 1;
    for (int p = 2; p * p <= k; p++) {  // trial division (Theorem 2.1.5)
        int e = 0;
        while (k % p == 0) k /= p, e++;
        if (e > 0) ways = ways * C(e + n - 1, n - 1) % MOD;
    }
    if (k > 1) ways = ways * C(n, n - 1) % MOD;  // the leftover prime, exponent 1
    return ways;
}
// snippet:end

int main() {
    vector<long long> fact(N + 1, 1), inv(N + 1, 1);
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N] = power(fact[N], MOD - 2);
    for (int i = N; i >= 1; i--) inv[i - 1] = inv[i] * i % MOD;
    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;
        cout << productWays(n, k, fact, inv) << "\n";
    }
}
