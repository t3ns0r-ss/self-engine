/*
Problem: for n integers, print the indices in the order a stable sort puts their values (equal
values by index), then, for each index in input order, its place in that order.
Indices and places are numbered from 1.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the indices in sorted order; line 2: place_1 .. place_n.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);  // (value, index): the index travels with its value
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());  // by value, equal values by index (Theorem 1.1.4)
    vector<int> place(n);
    for (int k = 0; k < n; k++) place[v[k].second] = k;  // pos[p_k] = k
    for (int k = 0; k < n; k++) cout << v[k].second + 1 << (k + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << place[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
