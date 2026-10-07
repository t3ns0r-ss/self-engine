/*
Problem: an array of n integers and q queries "l r" (1-based, l <= r); print a_l + ... + a_r for each.
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q lines "l r".
Output: one sum per line.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> P(n + 1, 0);  // P[k] = sum of the first k elements; sums reach 2*10^14
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        P[i + 1] = P[i] + a;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;  // elements l..r (1-based) are a[l-1..r-1] (0-based)
        cout << P[r] - P[l - 1] << "\n";  // Theorem 1.2.1
    }
}
