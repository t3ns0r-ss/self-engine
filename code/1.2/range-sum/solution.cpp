/*
Problem: an array of n integers and q queries "l r" (1-based, l <= r); print a_l + ... + a_r for each.
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q lines "l r".
Output: one sum per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.1. P[k] = sum of the first k elements; the sum of a[l..r] (0-based) is P[r + 1] - P[l].
vector<long long> prefixSums(const vector<long long>& a) {
    vector<long long> P(a.size() + 1, 0);
    for (int i = 0; i < (int)a.size(); i++) P[i + 1] = P[i] + a[i];
    return P;
}
long long rangeSum(const vector<long long>& P, int l, int r) { return P[r + 1] - P[l]; }
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<long long> P = prefixSums(a);
    while (q--) {
        int l, r;
        cin >> l >> r;  // elements l..r (1-based) are a[l-1..r-1] (0-based)
        cout << rangeSum(P, l - 1, r - 1) << "\n";
    }
}
