/*
Problem: AtCoder ABC 145 D, Knight.
Input: X Y (1 <= X, Y <= 10^6).
Output: the number of ways to reach (X, Y) from (0, 0) with moves (+1, +2) and (+2, +1), modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long power(long long a, long long b) {
    long long r = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main() {
    long long X, Y;
    cin >> X >> Y;
    // a moves (+1, +2) and b moves (+2, +1): a + 2b = X and 2a + b = Y
    if ((2 * Y - X) % 3 != 0 || 2 * Y < X || 2 * X < Y) {
        cout << 0 << "\n";
        return 0;
    }
    long long a = (2 * Y - X) / 3, b = (2 * X - Y) / 3, n = a + b;
    vector<long long> fact(n + 1, 1);
    for (long long i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    // a move sequence is fixed by which of the n moves are of the first kind: C(n, a)
    cout << fact[n] * power(fact[a], MOD - 2) % MOD * power(fact[b], MOD - 2) % MOD << "\n";
}
