/*
Problem: n zeros; q updates "l r v" add v to every element from l to r (1-based). Print the final array.
Input: n q (1 <= n, q <= 2*10^5), then q lines "l r v" (1 <= l <= r <= n, |v| <= 10^9).
Output: the n final values.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> d(n + 2, 0);  // difference array; index n + 1 absorbs updates ending at n
    while (q--) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        d[l] += v;      // the value starts rising at l
        d[r + 1] -= v;  // and drops back after r (Theorem 1.2.3, part 2)
    }
    long long cur = 0;  // running sum of d; values reach 2*10^14
    for (int i = 1; i <= n; i++) {
        cur += d[i];
        cout << cur << (i < n ? ' ' : '\n');
    }
}
