/*
Problem: replace every value by its rank, the number of distinct values smaller than it.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the number of distinct values d; line 2: the n ranks (each from 0 to d - 1).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);  // (value, index)
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    vector<int> rank(n);
    int r = 0;
    for (int k = 0; k < n; k++) {
        if (k > 0 && v[k].first != v[k - 1].first) r++;  // a new distinct value (Theorem 1.1.5)
        rank[v[k].second] = r;
    }
    cout << r + 1 << "\n";
    for (int i = 0; i < n; i++) cout << rank[i] << (i + 1 < n ? ' ' : '\n');
}
