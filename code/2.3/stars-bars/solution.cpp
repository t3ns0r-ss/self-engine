/*
Problem: count the solutions of x_1 + ... + x_k = n in integers with x_i >= l_i.
Input: n k (0 <= n <= 10^6, 1 <= k <= 10^6), then l_1 .. l_k (0 <= l_i <= 10^6).
Output: the count modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    cin >> n >> k;
    long long L = 0;
    for (int i = 0; i < k; i++) {
        long long l;
        cin >> l;
        L += l;
    }
    if (L > n) {  // even the lower bounds exceed n
        cout << 0 << "\n";
        return 0;
    }
    long long top = n - L + k - 1;  // y_i = x_i - l_i >= 0 sum to n - L: C(top, k - 1)  (Theorem 2.3.5)
    vector<long long> fact(top + 1);
    fact[0] = 1;
    for (long long i = 1; i <= top; i++) fact[i] = fact[i - 1] * i % MOD;
    long long ans = fact[top] * power(fact[k - 1], MOD - 2) % MOD * power(fact[top - (k - 1)], MOD - 2) % MOD;
    cout << ans << "\n";
}
