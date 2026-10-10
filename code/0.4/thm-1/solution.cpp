#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.1. a mod m in [0, m) for any sign of a, built from C++'s % (which is negative for negative a).
long long modNorm(long long a, long long m) { return (a % m + m) % m; }
// snippet:end

int main() {
    for (auto [a, m] : {pair{7, 5}, pair{-7, 5}, pair{-5, 5}})
        cout << "a = " << a << ", m = " << m << ": a % m = " << a % m << ", a mod m = " << modNorm(a, m) << '\n';
    for (int a = -60; a <= 60; a++)
        for (int m = 1; m <= 12; m++) {
            long long r = a;
            while (r < 0) r += m;  // the definition: the unique r in [0, m) with a = q m + r
            while (r >= m) r -= m;
            if (modNorm(a, m) != r) return 1;
        }
}
