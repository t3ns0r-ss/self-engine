/*
Problem: two lists a (n values) and b (m values).
Output line 1: the number of pairs (i, j) with b[j] < a[i].
Output line 2: the smallest |a[i] - b[j]| over all pairs.
Input: n m, then a[0..n-1], then b[0..m-1] (any order; n, m >= 1).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);  // differences of values up to 10^9 reach 2*10^9
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long pairs = 0;  // up to n*m
    long long closest = LLONG_MAX;
    int j = 0;  // j = number of b values less than a[i] (Theorem 1.3.5)
    for (int i = 0; i < n; i++) {
        while (j < m && b[j] < a[i]) j++;
        pairs += j;
        if (j < m) closest = min(closest, b[j] - a[i]);      // first b >= a[i]
        if (j > 0) closest = min(closest, a[i] - b[j - 1]);  // last b < a[i]
    }
    cout << pairs << "\n" << closest << "\n";
}
