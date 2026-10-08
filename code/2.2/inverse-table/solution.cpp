/*
Problem: the inverses of 1..n modulo a prime p.
Input: n p (1 <= n < p, n <= 10^6, p prime, p <= 10^9 + 7).
Output: inv[n], then the sum inv[1] + ... + inv[n] mod p.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, p;
    cin >> n >> p;
    vector<long long> inv(n + 1);
    inv[1] = 1;
    for (long long i = 2; i <= n; i++)
        inv[i] = (p - (p / i) * inv[p % i] % p) % p;  // -(p/i) * inv[p mod i]  (Theorem 2.2.6)
    long long sum = 0;
    for (long long i = 1; i <= n; i++) sum = (sum + inv[i]) % p;
    cout << inv[n] << " " << sum << "\n";
}
