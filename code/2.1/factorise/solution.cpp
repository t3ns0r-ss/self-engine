/*
Problem: factorise one number and report its divisor count and divisor sum.
Input: n (2 <= n <= 10^12).
Output: line 1: the factorisation as "p^e" terms in increasing order of p;
        line 2: d(n) and sigma(n), the number and the sum of the divisors of n.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 2.1.5 and 2.1.3. Trial division gives the primes with exponents; then d(n) and sigma(n) by the product formulas.
vector<pair<long long, int>> factorise(long long n) {
    vector<pair<long long, int>> f;  // (prime, exponent)
    for (long long d = 2; d * d <= n; d++) {
        if (n % d != 0) continue;
        int e = 0;
        while (n % d == 0) n /= d, e++;  // d is prime here
        f.push_back({d, e});
    }
    if (n > 1) f.push_back({n, 1});  // the leftover is a prime factor
    return f;
}
pair<long long, long long> divisorCountSum(const vector<pair<long long, int>>& f) {
    long long cnt = 1, sum = 1;
    for (auto [p, e] : f) {
        long long term = 1, pw = 1;  // term = 1 + p + ... + p^e
        for (int k = 1; k <= e; k++) pw *= p, term += pw;
        cnt *= e + 1;
        sum *= term;
    }
    return {cnt, sum};
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    auto f = factorise(n);
    for (int i = 0; i < (int)f.size(); i++)
        cout << f[i].first << "^" << f[i].second << (i + 1 < (int)f.size() ? ' ' : '\n');
    auto [cnt, sum] = divisorCountSum(f);
    cout << cnt << " " << sum << "\n";
}
