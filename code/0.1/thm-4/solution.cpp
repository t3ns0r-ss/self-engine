#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.4. floor(a / b) and ceil(a / b) for b > 0 and any sign of a.
long long floorDiv(long long a, long long b) {
    long long q = a / b;           // truncated toward zero
    if (a % b != 0 && a < 0) q--;  // a negative non-multiple was rounded up: go one lower
    return q;
}
long long ceilDiv(long long a, long long b) { return -floorDiv(-a, b); }
// snippet:end

int main() {
    for (auto [a, b] : {pair{7, 2}, pair{-7, 2}, pair{-6, 4}})
        cout << "a = " << a << ", b = " << b << ": floor " << floorDiv(a, b) << ", ceiling " << ceilDiv(a, b) << '\n';
    for (int a = -60; a <= 60; a++)
        for (int b = 1; b <= 12; b++) {
            long long f = -1000, c = 1000;  // the definitions: largest q with q*b <= a, smallest q with q*b >= a
            for (long long q = -1000; q <= 1000; q++) {
                if (q * b <= a) f = q;
                if (q * b >= a) c = min(c, q);
            }
            if (f != floorDiv(a, b) || c != ceilDiv(a, b)) return 1;
        }
}
