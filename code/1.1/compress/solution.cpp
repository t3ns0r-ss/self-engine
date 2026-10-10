/*
Problem: replace every value by its rank, the number of distinct values smaller than it.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the number of distinct values d; line 2: the n ranks (each from 0 to d - 1).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.5. The rank of every value among the distinct values: ranks are 0 .. d-1 and keep the order.
vector<int> compress(const vector<int>& a) {
    int n = a.size();
    vector<pair<int, int>> v(n);  // (value, index)
    for (int i = 0; i < n; i++) v[i] = {a[i], i};
    sort(v.begin(), v.end());
    vector<int> rank(n);
    int r = 0;
    for (int k = 0; k < n; k++) {
        if (k > 0 && v[k].first != v[k - 1].first) r++;  // a new distinct value
        rank[v[k].second] = r;
    }
    return rank;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> rank = compress(a);
    cout << *max_element(rank.begin(), rank.end()) + 1 << "\n";
    for (int i = 0; i < n; i++) cout << rank[i] << (i + 1 < n ? ' ' : '\n');
}
