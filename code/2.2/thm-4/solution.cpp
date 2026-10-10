#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.4. A fraction P/Q modulo a prime p is P * Q^(-1); sums, products and quotients work on the residues.
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
long long fractionMod(long long P, long long Q, long long p) {
    return P % p * power(Q, p - 2, p) % p;
}
// snippet:end

int main() {
    const long long p = 7;
    cout << "1/2 mod 7 = " << fractionMod(1, 2, p) << ", 1/3 mod 7 = " << fractionMod(1, 3, p) << '\n';
    cout << "1/2 + 1/3 = 5/6 mod 7: " << (fractionMod(1, 2, p) + fractionMod(1, 3, p)) % p << " and " << fractionMod(5, 6, p) << '\n';
    cout << "1/3 mod 998244353 = " << fractionMod(1, 3, 998244353) << '\n';
    for (long long P = 0; P < 20; P++) for (long long Q = 1; Q < 20; Q++) for (long long P2 = 0; P2 < 20; P2++) for (long long Q2 = 1; Q2 < 20; Q2++) {
        if (Q % 7 == 0 || Q2 % 7 == 0) continue;
        long long sum = (fractionMod(P, Q, p) + fractionMod(P2, Q2, p)) % p;
        if (sum != fractionMod(P * Q2 + P2 * Q, Q * Q2, p)) return 1;
        if (P * Q2 == P2 * Q && fractionMod(P, Q, p) != fractionMod(P2, Q2, p)) return 1;
    }
}
