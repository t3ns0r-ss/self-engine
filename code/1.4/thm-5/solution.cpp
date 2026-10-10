#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.5. The real cube root of c by halving; a fixed number of steps reaches the precision.
long double cubeRoot(long long c) {
    long double lo = -1e6 - 1, hi = 1e6 + 1;  // (10^6)^3 = 10^18 bounds every answer
    for (int it = 0; it < 100; it++) {
        long double mid = (lo + hi) / 2;
        if (mid * mid * mid >= c) hi = mid;
        else lo = mid;
    }
    return hi;
}
// snippet:end

int main() {
    for (long long c : {27LL, 2LL, -8LL}) printf("cube root of %lld: %.6Lf\n", c, cubeRoot(c));
    for (long long c = -200; c <= 200; c++)
        if (fabsl(cubeRoot(c) - cbrtl((long double)c)) > 1e-9L) return 1;
}
