/*
Problem: n goods; good i has a_i units, each worth v_i. Take at most W units in total; print the
largest total value.
Input: n W (1 <= n <= 2*10^5, 0 <= W <= 10^18), then n lines "a_i v_i" (1 <= a_i <= 10^9,
1 <= v_i <= 10^4).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long W;
    cin >> n >> W;
    vector<pair<long long, long long>> good(n);  // (value per unit, units)
    for (auto& [v, a] : good) cin >> a >> v;
    sort(good.rbegin(), good.rend());  // most valuable units first (Theorem 1.5.3, part 2)
    long long total = 0;  // at most (2*10^5 * 10^9 units) * 10^4 = 2*10^18
    for (auto [v, a] : good) {
        long long take = min(a, W);  // as many units of this good as still fit
        total += take * v;
        W -= take;
    }
    cout << total << "\n";
}
