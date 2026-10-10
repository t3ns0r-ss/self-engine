/*
Problem: for n integers, print the indices in the order a stable sort puts their values (equal
values by index), then, for each index in input order, its place in that order.
Indices and places are numbered from 1.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the indices in sorted order; line 2: place_1 .. place_n.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.4. Sorts (value, index) pairs. order[k] = the original index of the k-th smallest value (equal values
// by index), place[i] = the place of a_i in that order.
void sortedPositions(const vector<int>& a, vector<int>& order, vector<int>& place) {
    int n = a.size();
    vector<pair<int, int>> v(n);  // (value, index): the index travels with its value
    for (int i = 0; i < n; i++) v[i] = {a[i], i};
    sort(v.begin(), v.end());  // by value, equal values by index
    order.assign(n, 0), place.assign(n, 0);
    for (int k = 0; k < n; k++) order[k] = v[k].second, place[v[k].second] = k;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), order, place;
    for (auto& x : a) cin >> x;
    sortedPositions(a, order, place);
    for (int k = 0; k < n; k++) cout << order[k] + 1 << (k + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << place[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
