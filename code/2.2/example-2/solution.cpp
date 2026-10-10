/*
Problem: CSES 2182, Divisor Analysis.
Input: n (1 <= n <= 10^5), then n lines x k: x is a prime (2 <= x <= 10^6, all distinct), k its exponent (1 <= k <= 10^9).
Output: the number, the sum and the product of the divisors of x_1^k_1 * ... * x_n^k_n, each modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The number, the sum and the product of the divisors of prod x_i^k_i (distinct primes x_i), modulo 10^9 + 7.
const long long MOD = 1000000007;
long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
array<long long, 3> divisorAnalysis(const vector<pair<long long, long long>>& f) {
    long long cnt = 1, sum = 1, prod = 1;
    long long cntE = 1;  // the number of divisors so far, modulo MOD - 1, for exponents
    for (auto [x, k] : f) {
        cnt = cnt * ((k + 1) % MOD) % MOD;
        // 1 + x + ... + x^k = (x^(k+1) - 1) / (x - 1), with x - 1 not a multiple of MOD
        long long geo = (power(x, k + 1, MOD) - 1 + MOD) % MOD * power(x - 1, MOD - 2, MOD) % MOD;
        sum = sum * geo % MOD;
        // divisors of m * x^k are d * x^j: product = prod^(k+1) * x^((0 + ... + k) * cnt)
        long long tri = (k * (k + 1) / 2) % (MOD - 1);  // exponent reduced mod MOD - 1 (Theorem 2.2.5)
        prod = power(prod, k + 1, MOD) * power(x, tri * cntE % (MOD - 1), MOD) % MOD;
        cntE = cntE * ((k + 1) % (MOD - 1)) % (MOD - 1);
    }
    return {cnt, sum, prod};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> f(n);
    for (auto& [x, k] : f) cin >> x >> k;
    auto r = divisorAnalysis(f);
    cout << r[0] << " " << r[1] << " " << r[2] << "\n";
}
