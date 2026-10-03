/*
Problem: (a_1 b_1 + a_2 b_2 + ... + a_n b_n) mod m, as a value in [0, m).
Input: n m, then n lines "a_i b_i" (n <= 10^5, 1 <= m <= 2*10^9, |a_i|, |b_i| <= 10^18).
Output: the remainder.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m;
    cin >> n >> m;
    auto norm = [&](long long x) { return (x % m + m) % m; };  // a value in [0, m) (Theorem 0.4.1)
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        // reduce first: both factors are below m <= 2*10^9, so the product is below 4*10^18
        ans = (ans + norm(a) * norm(b)) % m;  // Theorem 0.4.4
    }
    cout << ans << "\n";
}
