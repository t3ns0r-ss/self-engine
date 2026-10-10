/*
Problem: count the solutions of x_1 + ... + x_k = n in integers with x_i >= l_i.
Input: n k (0 <= n <= 10^6, 1 <= k <= 10^6), then l_1 .. l_k (0 <= l_i <= 10^6).
Output: the count modulo 998244353.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.5. Solutions of x_1 + ... + x_k = n with x_i >= l_i: C(n - L + k - 1, k - 1), L = sum of the l_i.
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
long long starsBars(long long n, long long k, long long L) {
    if (L > n) return 0;  // even the lower bounds exceed n
    long long top = n - L + k - 1;
    vector<long long> fact(top + 1);
    fact[0] = 1;
    for (long long i = 1; i <= top; i++) fact[i] = fact[i - 1] * i % MOD;
    return fact[top] * power(fact[k - 1], MOD - 2) % MOD * power(fact[top - (k - 1)], MOD - 2) % MOD;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k, L = 0;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        long long l;
        cin >> l;
        L += l;
    }
    cout << starsBars(n, k, L) << "\n";
}
