#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 998244353;
    long long m, k;
    cin >> m >> k;
    long long tuples = 1;
    for (int i = 0; i < k; i++) tuples *= m;
    long long sum = 0;
    for (long long t = 0; t < tuples; t++) {  // every tuple, as a number in base m
        long long x = t, mx = 0;
        for (int i = 0; i < k; i++) mx = max(mx, x % m + 1), x /= m;
        sum += mx;
    }
    long long g = gcd(sum, tuples);
    sum /= g, tuples /= g;
    long long inv = 1;
    for (long long e = MOD - 2, b = tuples % MOD; e > 0; e >>= 1, b = b * b % MOD)
        if (e & 1) inv = inv * b % MOD;
    cout << sum % MOD * inv % MOD << "\n";
}
