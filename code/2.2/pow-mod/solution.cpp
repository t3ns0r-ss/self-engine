/*
Problem: compute a^b mod m for t queries.
Input: t (1 <= t <= 10^5), then t lines a b m (0 <= a, b <= 10^18, 1 <= m <= 10^18).
Output: a^b mod m for each query.
*/
#include <bits/stdc++.h>
using namespace std;

long long mulmod(long long x, long long y, long long m) {
    return (long long)((__int128)x * y % m);  // the product needs 128 bits when m > 3*10^9
}

long long power(long long a, long long b, long long m) {
    long long r = 1 % m, x = a % m;
    while (b > 0) {  // invariant: r * x^b = a^b (mod m)  (Theorem 2.2.1)
        if (b & 1) r = mulmod(r, x, m);
        x = mulmod(x, x, m);
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, m;
        cin >> a >> b >> m;
        cout << power(a, b, m) << "\n";
    }
}
