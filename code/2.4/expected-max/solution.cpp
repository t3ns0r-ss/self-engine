/*
Problem: k independent numbers are drawn uniformly from 1..m; print the expected maximum modulo 998244353.
Input: m k (1 <= m <= 10^6, 1 <= k <= 10^9).
Output: E[max] as P * Q^(-1) mod 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

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

int main() {
    long long m, k;
    cin >> m >> k;
    long long invMk = power(power(m, k), MOD - 2);  // 1 / m^k
    long long e = 0;
    for (long long x = 1; x <= m; x++) {
        // P(max >= x) = 1 - P(all < x) = 1 - ((x - 1)/m)^k  (Theorem 2.4.4)
        long long allBelow = power(x - 1, k) * invMk % MOD;
        e = (e + 1 - allBelow + MOD) % MOD;
    }
    cout << e << "\n";
}
