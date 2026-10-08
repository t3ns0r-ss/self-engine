/*
Problem: n kinds of coupons, each draw is uniformly random; you already own c different kinds.
Print the expected number of further draws until you own all n kinds, modulo 998244353.
Input: n c (1 <= n <= 10^6, 0 <= c < n).
Output: the expected value as P * Q^(-1) mod 998244353.
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
    long long n, c;
    cin >> n >> c;
    long long e = 0;
    for (long long j = c; j < n; j++) {
        // with j kinds owned, a draw is new with probability (n - j)/n: n/(n - j) draws on average
        e = (e + n % MOD * power(n - j, MOD - 2)) % MOD;  // stages add (Theorem 2.4.5)
    }
    cout << e << "\n";
}
