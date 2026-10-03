/*
Problem: for each query, count the multiples of k in [l, r].
Input: q, then q lines "l r k" (-10^18 <= l <= r <= 10^18, 1 <= k <= 10^18).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

// floor(a / b) for b > 0 and any sign of a (Theorem 0.1.4): C++ rounds toward zero
long long floorDiv(long long a, long long b) {
    return a / b - (a % b != 0 && a < 0 ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long l, r, k;
        cin >> l >> r >> k;
        // multiples of k that are <= r, minus those that are <= l - 1 (Theorem 0.4.2)
        cout << floorDiv(r, k) - floorDiv(l - 1, k) << "\n";
    }
}
