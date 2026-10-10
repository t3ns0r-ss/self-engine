#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.1. a^b mod m with at most log2(b) + 1 rounds: square the base, multiply it in at each set bit of b.
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
// snippet:end

int main() {
    cout << "3^13 mod 1000 = " << power(3, 13, 1000) << '\n';
    cout << "2^(10^18) mod (10^9 + 7) = " << power(2, 1000000000000000000LL, 1000000007) << '\n';
    cout << "5^0 mod 1 = " << power(5, 0, 1) << ", 0^0 mod 7 = " << power(0, 0, 7) << '\n';
    for (long long a = 0; a <= 12; a++)
        for (long long b = 0; b <= 20; b++)
            for (long long m = 1; m <= 30; m++) {
                long long r = 1 % m;
                for (int i = 0; i < b; i++) r = r * a % m;
                if (r != power(a, b, m)) return 1;
            }
}
