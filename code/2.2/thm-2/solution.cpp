#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.2. For a prime p: a^(p-1) = 1 (mod p) when p does not divide a, and a^p = a (mod p) always.
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
bool fermatHolds(long long a, long long p) {
    if (power(a, p, p) != a % p) return false;
    return a % p == 0 || power(a, p - 1, p) == 1;
}
// snippet:end

int main() {
    cout << "3^6 mod 7 = " << power(3, 6, 7) << '\n';
    cout << "3^3 mod 4 = " << power(3, 3, 4) << " (4 is not prime)\n";
    for (long long p : {2, 3, 5, 7, 11, 13, 998244353, 1000000007})
        for (long long a = 0; a < 40; a++) if (!fermatHolds(a, p)) return 1;
}
