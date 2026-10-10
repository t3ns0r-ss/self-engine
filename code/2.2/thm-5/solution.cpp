#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.5. For a prime p with p not dividing a: a^e = a^(e mod (p-1)) (mod p). A multiple of p gives 0 for e >= 1.
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
long long powerReduced(long long a, long long e, long long p) {
    if (a % p == 0) return e == 0 ? 1 : 0;
    return power(a, e % (p - 1), p);
}
// snippet:end

int main() {
    cout << "3^100 mod 7 = 3^(100 mod 6) = 3^4 mod 7 = " << powerReduced(3, 100, 7) << '\n';
    cout << "7^6 mod 7 = " << powerReduced(7, 6, 7) << " (a multiple of p is not reduced)\n";
    cout << "2^(10^18) mod (10^9 + 7) = " << powerReduced(2, 1000000000000000000LL, 1000000007) << '\n';
    for (long long p : {2, 3, 5, 7, 11, 13})
        for (long long a = 0; a < 30; a++)
            for (long long e = 0; e < 60; e++)
                if (power(a, e, p) != powerReduced(a, e, p)) return 1;
}
