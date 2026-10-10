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
int main() {
    // P1: 3^13 mod 1000. Brute: 13 multiplications. Method: squaring.
    cout << "P1 brute=" << slowPower(3, 13, 1000) << " method=" << power(3, 13, 1000) << '\n';
    // N1: 1000 mod 2^40, computing the modulus 2^40 in a 32-bit unsigned variable.
    unsigned int modulus = (unsigned int)(1ULL << 40);
    cout << "N1 brute=" << 1000 << " method=" << (modulus == 0 ? string("mod-by-zero") : to_string(1000 % modulus)) << '\n';
    // N2: the sum 1 + 3 + ... + 3^9 modulo 1000, computed as (3^10 - 1) / 2 after reducing 3^10.
    long long brute = 0, term = 1;
    for (int i = 0; i < 10; i++) brute = (brute + term) % 1000, term = term * 3 % 1000;
    long long wrong = (power(3, 10, 1000) - 1 + 1000) % 1000 / 2;
    cout << "N2 brute=" << brute << " method=" << wrong << '\n';
}
