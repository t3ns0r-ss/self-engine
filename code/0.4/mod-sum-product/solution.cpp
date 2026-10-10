/*
Problem: (a_1 b_1 + a_2 b_2 + ... + a_n b_n) mod m, as a value in [0, m).
Input: n m, then n lines "a_i b_i" (n <= 10^5, 1 <= m <= 2*10^9, |a_i|, |b_i| <= 10^18).
Output: the remainder.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 0.4.1 and 0.4.4. (a_1 b_1 + ... + a_n b_n) mod m as a value in [0, m). Reduce every factor first.
long long sumOfProducts(const vector<pair<long long, long long>>& v, long long m) {
    auto norm = [&](long long x) { return (x % m + m) % m; };  // a value in [0, m)
    long long ans = 0;
    for (auto [a, b] : v) ans = (ans + norm(a) * norm(b)) % m;  // both factors < m <= 2*10^9: product < 4*10^18
    return ans;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m;
    cin >> n >> m;
    vector<pair<long long, long long>> v(n);
    for (auto& p : v) cin >> p.first >> p.second;
    cout << sumOfProducts(v, m) << "\n";
}
