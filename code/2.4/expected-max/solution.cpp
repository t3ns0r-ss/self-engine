/*
Problem: k independent numbers are drawn uniformly from 1..m; print the expected maximum modulo 998244353.
Input: m k (1 <= m <= 10^6, 1 <= k <= 10^9).
Output: E[max] as P * Q^(-1) mod 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
const long long MOD = 998244353;
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
// Theorem 2.4.4. E[max of k draws from 1..m] = sum over x of P(max >= x) = 1 - ((x - 1)/m)^k, modulo 998244353.
long long expectedMax(long long m, long long k) {
    long long invMk = power(power(m, k), MOD - 2), e = 0;
    for (long long x = 1; x <= m; x++) {
        long long allBelow = power(x - 1, k) * invMk % MOD;
        e = (e + 1 - allBelow + MOD) % MOD;
    }
    return e;
}
// snippet:end

int main() {
    long long m, k;
    cin >> m >> k;
    cout << expectedMax(m, k) << "\n";
}
