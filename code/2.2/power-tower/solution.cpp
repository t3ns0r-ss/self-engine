/*
Problem: compute a^(b^c) mod p for t queries, with 0^0 = 1.
Input: t (1 <= t <= 10^5), then t lines a b c p (0 <= a, b, c <= 10^9, p prime, 2 <= p <= 10^9 + 7).
Output: a^(b^c) mod p for each query.
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
// Theorem 2.2.5. a^(b^c) mod the prime p, with 0^0 = 1: reduce the exponent b^c modulo p - 1, unless p divides a.
long long tower(long long a, long long b, long long c, long long p) {
    bool expZero = (b == 0 && c > 0);  // b^c = 0 exactly then
    if (a % p == 0) return expZero ? 1 : 0;
    long long e = power(b, c, p - 1);
    return power(a, e, p);
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, p;
        cin >> a >> b >> c >> p;
        cout << tower(a, b, c, p) << "\n";
    }
}
