/*
Problem: compute a^(b^c) mod p for t queries, with 0^0 = 1.
Input: t (1 <= t <= 10^5), then t lines a b c p (0 <= a, b, c <= 10^9, p prime, 2 <= p <= 10^9 + 7).
Output: a^(b^c) mod p for each query.
*/
#include <bits/stdc++.h>
using namespace std;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, p;
        cin >> a >> b >> c >> p;
        bool expZero = (b == 0 && c > 0);  // b^c = 0 exactly then (0^0 = 1)
        if (a % p == 0) {                   // p divides a (Theorem 2.2.5, part 2)
            cout << (expZero ? 1 : 0) << "\n";
            continue;
        }
        long long e = power(b, c, p - 1);   // the exponent modulo p - 1 (part 1)
        cout << power(a, e, p) << "\n";
    }
}
