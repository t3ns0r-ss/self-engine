/*
Problem: the sum of n fractions, printed modulo 998244353.
Input: n (1 <= n <= 2*10^5), then n lines P Q (0 <= P <= 10^9, 1 <= Q <= 10^9).
Output: (P_1/Q_1 + ... + P_n/Q_n) mod 998244353, that is, the sum as a fraction R/S printed as R * S^(-1).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) {  // invariant: r * a^b = (the answer) mod m
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
// Theorems 2.2.3 and 2.2.4. The sum of P/Q fractions as residues modulo the prime MOD: add P * Q^(MOD-2).
long long sumFractions(const vector<pair<long long, long long>>& f, long long MOD) {
    long long sum = 0;
    for (auto [P, Q] : f) {
        long long inv = power(Q, MOD - 2, MOD);  // Q^(-1) by Fermat
        sum = (sum + P % MOD * inv) % MOD;
    }
    return sum;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> f(n);
    for (auto& [P, Q] : f) cin >> P >> Q;
    cout << sumFractions(f, 998244353) << "\n";
}
