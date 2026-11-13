#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.4. x = r (mod m) and x = r2 (mod m2) have a common solution exactly when r = r2 (mod gcd(m, m2)); then
// the solutions are one residue class modulo lcm(m, m2). On success r becomes the smallest non-negative solution, m the lcm.
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
    if ((r2 - r) % g != 0) return false;
    long long m2g = m2 / g, lcm = m / g * m2;
    long long k = (long long)((__int128)((r2 - r) / g % m2g + m2g) % m2g * ((p % m2g + m2g) % m2g) % m2g);
    r += m * k, m = lcm;                                       // r + m*k < lcm because k < m2 / g
    return true;
}
// snippet:end

int main() {
    long long cases[][4] = {{2, 6, 8, 10}, {1, 4, 2, 6}, {3, 4, 3, 6}, {2, 3, 3, 5}};
    for (auto& cs : cases) {
        long long r = cs[0], m = cs[1];
        if (mergeCongruence(r, m, cs[2], cs[3])) cout << "x = " << cs[0] << " (mod " << cs[1] << "), x = " << cs[2] << " (mod " << cs[3] << "): x = " << r << " (mod " << m << ")\n";
        else cout << "x = " << cs[0] << " (mod " << cs[1] << "), x = " << cs[2] << " (mod " << cs[3] << "): no solution\n";
    }
    for (long long m = 1; m <= 14; m++)
        for (long long m2 = 1; m2 <= 14; m2++)
            for (long long r = 0; r < m; r++)
                for (long long r2 = 0; r2 < m2; r2++) {
                    long long best = -1, L = m / __gcd(m, m2) * m2;
                    for (long long x = 0; x < L && best < 0; x++)
                        if (x % m == r && x % m2 == r2) best = x;
                    long long rr = r, mm = m;
                    bool ok = mergeCongruence(rr, mm, r2, m2);
                    if (ok != (best >= 0) || (ok && (rr != best || mm != L))) return 1;
                }
}
