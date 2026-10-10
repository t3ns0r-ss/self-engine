#include <bits/stdc++.h>
using namespace std;

long long gcdLL(long long a, long long b) { return b == 0 ? a : gcdLL(b, a % b); }

int main() {
    // P1: gcd(1071, 462). Brute: the largest common divisor. Method: Euclid.
    int best = 0;
    for (int d = 1; d <= 462; d++) if (1071 % d == 0 && 462 % d == 0) best = d;
    cout << "P1 brute=" << best << " method=" << gcdLL(1071, 462) << '\n';
    // N1: lcm(12, 18) computed as a * b. Brute: the smallest common multiple.
    int l = 1;
    while (l % 12 != 0 || l % 18 != 0) l++;
    cout << "N1 brute=" << l << " method=" << 12 * 18 << '\n';
    // N2: lcm(4*10^9, 6*10^9) as a * b / gcd, where a * b overflows. Brute: 128-bit arithmetic.
    long long a = 4000000000LL, b = 6000000000LL;
    __int128 exact = (__int128)a * b / gcdLL(a, b);
    unsigned long long wrapped = (unsigned long long)a * (unsigned long long)b;  // what a * b becomes in 64 bits
    long long method = (long long)wrapped / gcdLL(a, b);
    cout << "N2 brute=" << (long long)exact << " method=" << method << '\n';
}
