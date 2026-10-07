/*
Problem: n items with values v_i; print the fewest items whose values add up to at least T, or -1.
Input: n T (1 <= n <= 2*10^5, 1 <= T <= 10^18), then v_1 .. v_n (1 <= v_i <= 10^9).
Output: the fewest number of items, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> v(n);
    for (auto& x : v) cin >> x;
    sort(v.rbegin(), v.rend());  // largest first (Theorem 1.5.3, part 1)
    long long sum = 0;           // up to 2*10^14
    for (int k = 0; k < n; k++) {
        sum += v[k];
        if (sum >= T) {
            cout << k + 1 << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
}
