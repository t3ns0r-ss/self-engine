#include <bits/stdc++.h>
using namespace std;

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

// number of (x, y) with x, y >= 0 and a*x + b*y = c, a, b > 0, from one solution and the step b / g
long long countNonNegative(long long a, long long b, long long c) {
    long long p, q, g = extGcd(a, b, p, q);
    if (c % g != 0) return 0;
    long long sa = a / g, sb = b / g, cg = c / g;
    // x = x0 + t*sb, y = y0 - t*sa, with (x0, y0) = (p*cg, q*cg)
    __int128 x0 = (__int128)p * cg, y0 = (__int128)q * cg;
    auto fl = [](__int128 u, __int128 v) { __int128 d = u / v; return u % v < 0 ? d - 1 : d; };
    __int128 lo = -fl(x0, sb);               // x >= 0  <=>  t >= ceil(-x0 / sb)
    lo = -fl(x0, sb);
    __int128 hi = fl(y0, sa);                // y >= 0  <=>  t <= floor(y0 / sa)
    return hi < lo ? 0 : (long long)(hi - lo + 1);
}
long long bruteCount(long long a, long long b, long long c) {
    long long n = 0;
    for (long long x = 0; x * a <= c; x++) n += (c - a * x) % b == 0;
    return n;
}
int main() {
    // P1: pay exactly 100 with coins of 7 and 12 (non-negative counts)
    cout << "P1 brute=" << bruteCount(7, 12, 100) << " method=" << countNonNegative(7, 12, 100) << '\n';
    // P2: pay exactly 60 with coins of 6 and 10
    cout << "P2 brute=" << bruteCount(6, 10, 60) << " method=" << countNonNegative(6, 10, 60) << '\n';
    // N1: does 6x + 10y = 14 have an integer solution? The wrong method: "14 must be a multiple of 6 or of 10".
    bool truth = false;
    for (int x = -50; x <= 50; x++) for (int y = -50; y <= 50; y++) truth = truth || 6 * x + 10 * y == 14;
    cout << "N1 brute=" << truth << " method=" << (14 % 6 == 0 || 14 % 10 == 0) << '\n';
    // N2: the smallest non-negative x with 4x + 6y = 10. The wrong method keeps the x that extended Euclid gives, scaled by c / g.
    long long x, y, g = extGcd(4, 6, x, y);
    long long wrong = x * (10 / g), best = -1;
    for (long long t = 0; t < 100 && best < 0; t++) if ((10 - 4 * t) % 6 == 0) best = t;
    cout << "N2 brute=" << best << " method=" << wrong << '\n';
}
