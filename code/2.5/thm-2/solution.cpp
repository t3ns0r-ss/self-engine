#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.2. If (x0, y0) solves a*x + b*y = c and g = gcd(a, b), every solution is (x0 + t*b/g, y0 - t*a/g).
// The smallest non-negative x and its partner y (a, b > 0, g divides c):
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
bool smallestX(long long a, long long b, long long c, long long& x, long long& y) {
    long long p, q, g = extGcd(a, b, p, q);                    // a*p + b*q = g
    if (c % g != 0) return false;
    long long step = b / g;                                    // x moves in steps of b / g
    x = (long long)((__int128)(p % step + step) % step * ((c / g) % step) % step);
    y = (c - a * x) / b;
    return true;
}
// snippet:end

int main() {
    long long cases[][3] = {{6, 10, 14}, {7, 12, 100}, {4, 6, 10}, {5, 3, 1}};
    for (auto& cs : cases) {
        long long a = cs[0], b = cs[1], c = cs[2], x = 0, y = 0;
        if (!smallestX(a, b, c, x, y)) return 1;
        cout << a << "x + " << b << "y = " << c << ": smallest x = " << x << ", y = " << y << "\n";
        if (a * x + b * y != c || x < 0 || x >= b / __gcd(a, b)) return 1;
    }
    for (long long a = 1; a <= 15; a++)
        for (long long b = 1; b <= 15; b++)
            for (long long c = 0; c <= 60; c++) {
                long long best = -1;
                for (long long x = 0; x <= 200 && best < 0; x++)
                    if ((c - a * x) % b == 0) best = x;
                long long x, y;
                bool ok = smallestX(a, b, c, x, y);
                if (ok != (best >= 0) || (ok && x != best)) return 1;
            }
}
