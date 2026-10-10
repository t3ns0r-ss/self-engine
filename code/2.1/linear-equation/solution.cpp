/*
Problem: find integers x, y with a*x + b*y = c and the smallest possible x >= 0.
Input: t (1 <= t <= 10^5), then t lines a b c (1 <= a, b <= 10^9, 0 <= c <= 10^18).
Output: for each line, "x y" for that solution, or -1 if there is no integer solution.
*/
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
// The solution of a*x + b*y = c with the smallest x >= 0, or false when gcd(a, b) does not divide c.
bool solveLinear(long long a, long long b, long long c, long long& x0, long long& y0) {
    long long x, y;
    long long g = ext(a, b, x, y);
    if (c % g != 0) return false;
    long long m = b / g;  // x is determined modulo b/g (part 4)
    long long xm = ((x % m) + m) % m, cm = (c / g) % m;
    x0 = xm * cm % m;           // both factors below 10^9: no overflow
    y0 = (c - a * x0) / b;      // a * x0 < 10^18
    return true;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, x, y;
        cin >> a >> b >> c;
        if (solveLinear(a, b, c, x, y)) cout << x << " " << y << "\n";
        else cout << -1 << "\n";
    }
}
