/*
Problem: count the integer pairs (x, y) with a*x + b*y = c, x1 <= x <= x2 and y1 <= y <= y2.
Input: a b c x1 x2 y1 y2 (|a|, |b| <= 10^9, |c|, |x|, |y| bounds <= 10^18).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 2.5.1 and 2.5.2. One solution by extended Euclid, then the t for which x = X + t*b/g and y = Y - t*a/g stay in range.
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
__int128 floorDiv(__int128 a, __int128 b) {  // b != 0
    if (b < 0) a = -a, b = -b;
    __int128 q = a / b;
    return a % b < 0 ? q - 1 : q;
}
__int128 ceilDiv(__int128 a, __int128 b) { return -floorDiv(-a, b); }
// The t with lo <= P + t*s <= hi (s != 0), as a closed range [first, last].
pair<__int128, __int128> tRange(__int128 P, __int128 s, __int128 lo, __int128 hi) {
    if (s > 0) return {ceilDiv(lo - P, s), floorDiv(hi - P, s)};
    return {ceilDiv(hi - P, s), floorDiv(lo - P, s)};
}
long long countSolutions(long long a, long long b, long long c, long long x1, long long x2, long long y1, long long y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (a == 0 && b == 0) return c == 0 ? (x2 - x1 + 1) * (y2 - y1 + 1) : 0;
    if (a == 0) return (c % b == 0 && y1 <= c / b && c / b <= y2) ? x2 - x1 + 1 : 0;
    if (b == 0) return (c % a == 0 && x1 <= c / a && c / a <= x2) ? y2 - y1 + 1 : 0;
    long long u, v, g = extGcd(llabs(a), llabs(b), u, v);
    if (c % g != 0) return 0;
    __int128 X = (__int128)u * (a < 0 ? -1 : 1) * (c / g), Y = (__int128)v * (b < 0 ? -1 : 1) * (c / g);
    auto [lo1, hi1] = tRange(X, b / g, x1, x2);                // x = X + t * (b / g)
    auto [lo2, hi2] = tRange(Y, -(a / g), y1, y2);             // y = Y - t * (a / g)
    __int128 lo = max(lo1, lo2), hi = min(hi1, hi2);
    return hi < lo ? 0 : (long long)(hi - lo + 1);
}
// snippet:end

int main() {
    long long a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    cout << countSolutions(a, b, c, x1, x2, y1, y2) << "\n";
}
