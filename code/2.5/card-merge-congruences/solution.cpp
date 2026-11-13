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

// merge x = r (mod m) with x = r2 (mod m2); false when there is no solution
bool mergeCongruence(long long& r, long long& m, long long r2, long long m2) {
    r %= m, r2 %= m2;
    long long p, q, g = extGcd(m, m2, p, q);
    if ((r2 - r) % g != 0) return false;
    long long m2g = m2 / g, lcm = m / g * m2;
    long long k = (long long)((__int128)((r2 - r) / g % m2g + m2g) % m2g * ((p % m2g + m2g) % m2g) % m2g);
    r += m * k, m = lcm;
    return true;
}
long long bruteSmallest(vector<pair<long long, long long>> c) {
    for (long long x = 0; x < 100000; x++) {
        bool ok = true;
        for (auto [r, m] : c) ok = ok && x % m == r % m;
        if (ok) return x;
    }
    return -1;
}
long long methodSmallest(vector<pair<long long, long long>> c) {
    long long r = 0, m = 1;
    for (auto [r2, m2] : c) if (!mergeCongruence(r, m, r2, m2)) return -1;
    return r;
}
int main() {
    cout << "P1 brute=" << bruteSmallest({{2, 6}, {8, 10}}) << " method=" << methodSmallest({{2, 6}, {8, 10}}) << '\n';
    cout << "P2 brute=" << bruteSmallest({{2, 3}, {3, 5}, {2, 7}}) << " method=" << methodSmallest({{2, 3}, {3, 5}, {2, 7}}) << '\n';
    // N1: x = 1 (mod 4) and x = 2 (mod 6). The wrong method treats the moduli as coprime: x = r1*m2*q + r2*m1*p modulo m1*m2.
    long long p, q, g = extGcd(4, 6, p, q);
    (void)g;
    long long wrong = ((1 * 6 * q + 2 * 4 * p) % 24 + 24) % 24;
    cout << "N1 brute=" << bruteSmallest({{1, 4}, {2, 6}}) << " method=" << wrong << '\n';
    // N2: how many x in [0, 48) have x = 3 (mod 4) and x = 3 (mod 6)? The wrong method says the period is the product 24.
    int truth = 0;
    for (int x = 0; x < 48; x++) truth += x % 4 == 3 && x % 6 == 3;
    cout << "N2 brute=" << truth << " method=" << 48 / (4 * 6) << '\n';
}
