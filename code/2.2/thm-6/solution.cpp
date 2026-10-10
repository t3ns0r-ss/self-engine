#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.6. The inverses of 1..n modulo a prime p > n in O(n): inv[i] = -(p / i) * inv[p mod i] mod p.
vector<long long> inverseTable(long long n, long long p) {
    vector<long long> inv(n + 1);
    inv[1] = 1;
    for (long long i = 2; i <= n; i++)
        inv[i] = (p - (p / i) * inv[p % i] % p) % p;
    return inv;
}
// snippet:end

int main() {
    auto inv = inverseTable(6, 7);
    cout << "inverses modulo 7:";
    for (int i = 1; i <= 6; i++) cout << ' ' << inv[i];
    cout << '\n';
    for (long long p : {7, 101, 1009}) {
        auto t = inverseTable(p - 1, p);
        for (long long i = 1; i < p; i++) if (i * t[i] % p != 1) return 1;
    }
}
