/*
Problem: the smallest non-negative x with x = r_i (mod m_i) for every i, and the lcm of the moduli; or -1 if there is none.
Input: n, then n lines "r m" (1 <= m <= 10^9, the lcm of all moduli at most 10^18).
Output: "x lcm" or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.4, applied one congruence at a time. r is the smallest non-negative solution so far, m the lcm so far.
long long extGcd(long long a, long long b, long long& x, long long& y) {  // a, b >= 0, not both 0: a*x + b*y = gcd(a, b)
    x = 1, y = 0;
    long long x1 = 0, y1 = 1;
    while (b != 0) {
        long long q = a / b;
        tie(a, b) = make_pair(b, a - q * b);
        tie(x, x1) = make_pair(x1, x - q * x1);
        tie(y, y1) = make_pair(y1, y - q * y1);
    }
    return a;
}
bool mergeCongruence(long long& r, long long& m, long long r2, long long m2) {
    r %= m, r2 %= m2;
    long long p, q, g = extGcd(m, m2, p, q);                   // m*p + m2*q = g
    if ((r2 - r) % g != 0) return false;                       // the residues disagree modulo g
    long long m2g = m2 / g, lcm = m / g * m2;
    long long k = (long long)((__int128)((r2 - r) / g % m2g + m2g) % m2g * ((p % m2g + m2g) % m2g) % m2g);
    r += m * k, m = lcm;
    return true;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    long long r = 0, m = 1;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        long long ri, mi;
        cin >> ri >> mi;
        if (ok) ok = mergeCongruence(r, m, ri, mi);
    }
    if (ok) cout << r << " " << m << "\n";
    else cout << -1 << "\n";
}
