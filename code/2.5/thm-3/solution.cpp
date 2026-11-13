#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.5.3. a*x = b (mod m) has a solution exactly when g = gcd(a, m) divides b; the solutions are one residue class
// modulo m / g. The smallest non-negative one, or -1.
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
    a = (a % m + m) % m, b = (b % m + m) % m;
    long long x, y, g = extGcd(a, m, x, y);                    // a*x + m*y = g
    if (b % g != 0) return -1;
    long long mg = m / g;
    return (long long)((__int128)((x % mg + mg) % mg) * (b / g) % mg);
}
// snippet:end

int main() {
    long long cases[][3] = {{6, 4, 10}, {6, 3, 10}, {3, 2, 7}, {0, 0, 5}, {4, 6, 8}};
    for (auto& cs : cases) cout << cs[0] << "x = " << cs[1] << " (mod " << cs[2] << "): " << solveCongruence(cs[0], cs[1], cs[2]) << "\n";
    for (long long m = 1; m <= 40; m++)
        for (long long a = 0; a <= 45; a++)
            for (long long b = 0; b <= 45; b++) {
                long long best = -1;
                for (long long x = 0; x < m && best < 0; x++)
                    if ((a * x - b) % m == 0) best = x;
                if (solveCongruence(a, b, m) != best) return 1;
            }
}
