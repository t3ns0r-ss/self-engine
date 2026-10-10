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
    // P1: 1/2 + 1/3 as a value modulo 7. Brute: the x with 6x = 5 (mod 7), since 1/2 + 1/3 = 5/6. Method: P * Q^(p-2).
    long long brute = -1;
    for (long long x = 0; x < 7; x++) if (6 * x % 7 == 5) brute = x;
    long long method = (power(2, 5, 7) + power(3, 5, 7)) % 7;
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the inverse of 4 modulo 10, which is not prime. Brute: none (-1). Method: 4^(10-2) mod 10.
    long long bruteInv = -1;
    for (long long x = 0; x < 10; x++) if (4 * x % 10 == 1) bruteInv = x;
    cout << "N1 brute=" << bruteInv << " method=" << power(4, 8, 10) << '\n';
    // N2: 1 + 8 + 8^2 + 8^3 + 8^4 modulo 7, as (8^5 - 1) / (8 - 1) with the inverse of 8 - 1 = 7 modulo 7.
    long long sum = 0, t = 1;
    for (int i = 0; i < 5; i++) sum = (sum + t) % 7, t = t * 8 % 7;
    long long formula = (power(8, 5, 7) - 1 + 7) % 7 * power(7, 5, 7) % 7;
    cout << "N2 brute=" << sum << " method=" << formula << '\n';
}
