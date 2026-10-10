/*
Problem: the inverse of a modulo m, for t queries.
Input: t (1 <= t <= 10^5), then t lines a m (0 <= a <= 10^18, 2 <= m <= 10^18).
Output: the x in [0, m) with a*x = 1 (mod m), or -1 if gcd(a, m) != 1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.3, part 2. ext gives g = gcd(a, b) and x, y with a*x + b*y = g; then x is the inverse of a modulo m.
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
long long inverseMod(long long a, long long m) {  // -1 when gcd(a, m) != 1
    long long x, y;
    long long g = ext(a % m, m, x, y);  // (a mod m)*x + m*y = g
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, m;
        cin >> a >> m;
        cout << inverseMod(a, m) << "\n";
    }
}
