#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.2. ext returns g = gcd(a, b) and sets x, y with a*x + b*y = g.
long long ext(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1;
    long long g = ext(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
// One solution of a*x + b*y = c, or false when gcd(a, b) does not divide c. Others: (x + k*b/g, y - k*a/g).
bool oneSolution(long long a, long long b, long long c, long long& x, long long& y) {
    long long g = ext(a, b, x, y);
    if (c % g != 0) return false;
    x *= c / g, y *= c / g;
    return true;
}
// snippet:end

int main() {
    long long x, y;
    long long g = ext(240, 46, x, y);
    cout << "ext(240, 46): g = " << g << ", x = " << x << ", y = " << y << '\n';
    oneSolution(240, 46, 10, x, y);
    cout << "240x + 46y = 10: x = " << x << ", y = " << y << ", with k = 2: x = " << x + 2 * 23 << ", y = " << y - 2 * 120 << '\n';
    cout << "12x + 18y = 7: " << (oneSolution(12, 18, 7, x, y) ? "solvable" : "no solution") << '\n';
    for (long long a = 1; a <= 30; a++)
        for (long long b = 0; b <= 30; b++) {
            if (a == 0 && b == 0) continue;
            long long X, Y, G = ext(a, b, X, Y);
            if (G != __gcd(a, b) || a * X + b * Y != G) return 1;
            for (long long c = -20; c <= 20; c++) {
                bool brute = false;
                for (long long u = -60; u <= 60 && !brute; u++)
                    for (long long v = -60; v <= 60 && !brute; v++) brute = a * u + b * v == c;
                if (brute != (c % G == 0)) return 1;
            }
        }
}
