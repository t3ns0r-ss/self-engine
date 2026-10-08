/*
Problem: the sum of n fractions, printed modulo 998244353.
Input: n (1 <= n <= 2*10^5), then n lines P Q (0 <= P <= 10^9, 1 <= Q <= 10^9).
Output: (P_1/Q_1 + ... + P_n/Q_n) mod 998244353, that is, the sum as a fraction R/S printed as R * S^(-1).
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
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long P, Q;
        cin >> P >> Q;
        long long inv = power(Q, MOD - 2);  // Q^(-1) by Fermat (Theorem 2.2.3, part 3)
        sum = (sum + P % MOD * inv) % MOD;  // fractions add as residues (Theorem 2.2.4)
    }
    cout << sum << "\n";
}
