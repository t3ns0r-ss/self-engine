/*
Problem: for each query, count the multiples of k in [l, r].
Input: q, then q lines "l r k" (-10^18 <= l <= r <= 10^18, 1 <= k <= 10^18).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.2. Multiples of k in [l, r]. floor() is written out because C++ division rounds toward zero (Theorem 0.1.4).
long long floorDiv(long long a, long long b) { return a / b - (a % b != 0 && a < 0 ? 1 : 0); }

long long countMultiples(long long l, long long r, long long k) { return floorDiv(r, k) - floorDiv(l - 1, k); }
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long l, r, k;
        cin >> l >> r >> k;
        cout << countMultiples(l, r, k) << "\n";
    }
}
