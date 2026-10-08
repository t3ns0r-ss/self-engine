/*
Problem: AtCoder ABC 326 E, Revenge of "The Salary of AtCoder Inc.".
Input: N (1 <= N <= 3*10^5), then A_1 .. A_N (0 <= A_i < 998244353).
Output: the expected salary modulo 998244353.
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    long long invN = power(n, MOD - 2);
    long long grow = (1 + invN) % MOD;  // (1 + 1/N)
    long long pw = 1;                    // (1 + 1/N)^(y - 1)
    long long e = 0;
    for (long long y = 1; y <= n; y++) {
        long long a;
        cin >> a;
        long long p = invN * pw % MOD;   // P(A_y is paid) = (1/N)(1 + 1/N)^(y-1)
        e = (e + a % MOD * p) % MOD;     // linearity: add A_y times its probability (Theorem 2.4.2)
        pw = pw * grow % MOD;
    }
    cout << e << "\n";
}
