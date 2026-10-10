#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.5. floor(sqrt(x)) for 0 <= x <= 10^18: a floating-point guess, then corrected with integers.
long long isqrt(long long x) {
    long long r = sqrtl((long double)x);
    while (r > 0 && r * r > x) r--;      // too big: go down
    while ((r + 1) * (r + 1) <= x) r++;  // too small: go up
    return r;
}
// snippet:end

int main() {
    for (long long x : {10LL, 999999999999999999LL, 1000000000000000000LL})
        cout << "isqrt(" << x << ") = " << isqrt(x) << '\n';
    for (long long x = 0; x <= 20000; x++) {
        long long s = 0;
        while ((s + 1) * (s + 1) <= x) s++;
        if (isqrt(x) != s) return 1;
    }
    for (long long s = 999999000; s <= 1000000000; s += 997)
        for (long long d = -1; d <= 1; d++)
            if (isqrt(s * s + d) != (d < 0 ? s - 1 : s)) return 1;
}
