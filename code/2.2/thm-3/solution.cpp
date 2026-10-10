#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.3. The inverse of a modulo m: by extended Euclid (any m with gcd(a, m) = 1) or by a^(p-2) (m = p prime).
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
long long inverseExt(long long a, long long m) {  // -1 when gcd(a, m) != 1
    long long x, y;
    if (ext(a % m, m, x, y) != 1) return -1;
    return ((x % m) + m) % m;
}
long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) {  // invariant: r * a^b = (the answer) mod m
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
long long inversePrime(long long a, long long p) { return power(a, p - 2, p); }
// snippet:end

int main() {
    cout << "3^(-1) mod 7: " << inverseExt(3, 7) << " (Euclid), " << inversePrime(3, 7) << " (Fermat)\n";
    cout << "3^(-1) mod 10: " << inverseExt(3, 10) << ", 4^(-1) mod 10: " << inverseExt(4, 10) << " (none)\n";
    for (long long m = 2; m <= 60; m++)
        for (long long a = 1; a < m; a++) {
            long long brute = -1;
            for (long long x = 0; x < m; x++) if (a * x % m == 1) brute = x;
            if (brute != inverseExt(a, m)) return 1;
        }
    for (long long a = 1; a < 100; a++) if (inversePrime(a, 101) != inverseExt(a, 101)) return 1;
}
