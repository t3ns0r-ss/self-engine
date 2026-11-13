#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.1. a*x + b*y = c has integer solutions exactly when gcd(a, b) divides c; extended Euclid gives one.
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
bool solveOne(long long a, long long b, long long c, long long& x, long long& y) {  // a, b not both 0
    long long g = extGcd(llabs(a), llabs(b), x, y);          // |a|*x + |b|*y = g
    if (c % g != 0) return false;
    x *= (a < 0 ? -1 : 1) * (c / g);                          // restore the signs, then scale by c / g
    y *= (b < 0 ? -1 : 1) * (c / g);
    return true;
}
// snippet:end

int main() {
    long long cases[][3] = {{6, 10, 14}, {6, 10, 15}, {7, 12, 100}, {-4, 6, 2}, {9, 0, 27}};
    for (auto& cs : cases) {
        long long a = cs[0], b = cs[1], c = cs[2], x = 0, y = 0;
        if (solveOne(a, b, c, x, y)) {
            cout << a << "x + " << b << "y = " << c << ": x = " << x << ", y = " << y << "\n";
            if (a * x + b * y != c) return 1;
        } else {
            cout << a << "x + " << b << "y = " << c << ": no solution\n";
        }
    }
    for (long long a = -12; a <= 12; a++)
        for (long long b = -12; b <= 12; b++)
            for (long long c = -30; c <= 30; c++) {
                if (a == 0 && b == 0) continue;
                bool brute = false;
                for (long long x = -60; x <= 60 && !brute; x++)
                    for (long long y = -60; y <= 60 && !brute; y++) brute = a * x + b * y == c;
                long long x, y;
                if (solveOne(a, b, c, x, y) != brute) return 1;
            }
}
