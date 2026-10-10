#include <bits/stdc++.h>
using namespace std;

long long power(long long a, long long b, long long m) {
    long long r = 1 % m;
    a %= m;
    while (b > 0) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; }
    return r;
}
long long slowPower(long long a, long long b, long long m) {
    long long r = 1 % m;
    for (long long i = 0; i < b; i++) r = r * a % m;
    return r;
}
long long reduced(long long a, long long e, long long p) { return power(a, e % (p - 1), p); }
int main() {
    // P1: 3^100 mod 7. P2: 2^(3^4) mod 5. Brute: repeated multiplication. Method: reduce the exponent modulo p - 1.
    cout << "P1 brute=" << slowPower(3, 100, 7) << " method=" << reduced(3, 100, 7) << '\n';
    cout << "P2 brute=" << slowPower(2, 81, 5) << " method=" << reduced(2, 81, 5) << '\n';
    // N1: 7^6 mod 7, reducing the exponent 6 to 0 even though 7 is a multiple of the prime 7.
    cout << "N1 brute=" << slowPower(7, 6, 7) << " method=" << reduced(7, 6, 7) << '\n';
    // N2: 3^100 mod 10, reducing the exponent modulo 10 - 1 = 9 although 10 is not prime.
    cout << "N2 brute=" << slowPower(3, 100, 10) << " method=" << reduced(3, 100, 10) << '\n';
}
