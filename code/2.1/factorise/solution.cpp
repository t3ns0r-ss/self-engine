/*
Problem: factorise one number and report its divisor count and divisor sum.
Input: n (2 <= n <= 10^12).
Output: line 1: the factorisation as "p^e" terms in increasing order of p;
        line 2: d(n) and sigma(n), the number and the sum of the divisors of n.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<pair<long long, int>> f;  // (prime, exponent)
    for (long long d = 2; d * d <= n; d++) {
        if (n % d != 0) continue;
        int e = 0;
        while (n % d == 0) n /= d, e++;  // d is prime here (Theorem 2.1.5)
        f.push_back({d, e});
    }
    if (n > 1) f.push_back({n, 1});  // the leftover is a prime factor
    long long cnt = 1, sum = 1;
    for (int i = 0; i < (int)f.size(); i++) {
        auto [p, e] = f[i];
        long long term = 1, pw = 1;  // term = 1 + p + ... + p^e (Theorem 2.1.3)
        for (int k = 1; k <= e; k++) pw *= p, term += pw;
        cnt *= e + 1;
        sum *= term;
        cout << p << "^" << e << (i + 1 < (int)f.size() ? ' ' : '\n');
    }
    cout << cnt << " " << sum << "\n";
}
