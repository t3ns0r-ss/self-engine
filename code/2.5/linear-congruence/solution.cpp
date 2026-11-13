/*
Problem: the smallest x with 0 <= x < m and a*x = b (mod m), or -1.
Input: a b m (0 <= a, b <= 10^18, 1 <= m <= 10^9).
Output: x or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.3. Solvable exactly when gcd(a, m) divides b; the solutions are one class modulo m / g.
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
long long solveCongruence(long long a, long long b, long long m) {
    a %= m, b %= m;
    long long x, y, g = extGcd(a, m, x, y);                    // a*x + m*y = g, and g = m when a = 0
    if (b % g != 0) return -1;
    long long mg = m / g;
    return (long long)((__int128)((x % mg + mg) % mg) * (b / g) % mg);
}
// snippet:end

int main() {
    long long a, b, m;
    cin >> a >> b >> m;
    cout << solveCongruence(a, b, m) << "\n";
}
