/*
Problem: the inverses of 1..n modulo a prime p.
Input: n p (1 <= n < p, n <= 10^6, p prime, p <= 10^9 + 7).
Output: inv[n], then the sum inv[1] + ... + inv[n] mod p.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.2.6. inv[i] = -(p / i) * inv[p mod i] mod p, for 1 <= i <= n < p, in O(n).
vector<long long> inverseTable(long long n, long long p) {
    vector<long long> inv(n + 1);
    inv[1] = 1;
    for (long long i = 2; i <= n; i++)
        inv[i] = (p - (p / i) * inv[p % i] % p) % p;
    return inv;
}
// snippet:end

int main() {
    long long n, p;
    cin >> n >> p;
    vector<long long> inv = inverseTable(n, p);
    long long sum = 0;
    for (long long i = 1; i <= n; i++) sum = (sum + inv[i]) % p;
    cout << inv[n] << " " << sum << "\n";
}
