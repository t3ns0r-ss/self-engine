/*
Problem: n zeros; q updates "l r v" add v to every element from l to r (1-based). Print the final array.
Input: n q (1 <= n, q <= 2*10^5), then q lines "l r v" (1 <= l <= r <= n, |v| <= 10^9).
Output: the n final values.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.3. Add v to a[l..r] for every update (1-based), then read the whole array: one running sum.
vector<long long> rangeAdd(int n, const vector<array<long long, 3>>& updates) {
    vector<long long> d(n + 2, 0);  // difference array; index n + 1 absorbs updates ending at n
    for (auto [l, r, v] : updates) {
        d[l] += v;      // the value starts rising at l
        d[r + 1] -= v;  // and drops back after r
    }
    vector<long long> a(n);
    long long cur = 0;
    for (int i = 1; i <= n; i++) a[i - 1] = cur += d[i];
    return a;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<array<long long, 3>> updates(q);
    for (auto& u : updates) cin >> u[0] >> u[1] >> u[2];
    vector<long long> a = rangeAdd(n, updates);
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
