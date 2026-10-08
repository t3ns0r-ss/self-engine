/*
Problem: the inverse of a modulo m, for t queries.
Input: t (1 <= t <= 10^5), then t lines a m (0 <= a <= 10^18, 2 <= m <= 10^18).
Output: the x in [0, m) with a*x = 1 (mod m), or -1 if gcd(a, m) != 1.
*/
#include <bits/stdc++.h>
using namespace std;

// Returns g = gcd(a, b) and sets x, y with a*x + b*y = g (Theorem 2.1.2).
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, m;
        cin >> a >> m;
        long long x, y;
        long long g = ext(a % m, m, x, y);  // (a mod m)*x + m*y = g
        if (g != 1) {
            cout << -1 << "\n";  // no inverse (Theorem 2.2.3, part 1)
            continue;
        }
        cout << ((x % m) + m) % m << "\n";
    }
}
