/*
Drill (about 4 minutes). An array and q questions "sum of a[l..r]" (1-indexed, both ends included).
Input: n q, then a_1..a_n (|a_i| <= 10^9), then q lines "l r" with 1 <= l <= r <= n. n, q <= 2*10^5.
Output: one sum per line (it can reach 2*10^14, so use long long).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// pre[i] is the sum of the first i elements, so a[l..r] = pre[r] - pre[l - 1]. Index from 1.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a;
        pre[i] = pre[i - 1] + a;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pre[r] - pre[l - 1] << "\n";
    }
}
// snippet:end
