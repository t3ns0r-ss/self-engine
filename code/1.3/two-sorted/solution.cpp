/*
Problem: two lists a (n values) and b (m values).
Output line 1: the number of pairs (i, j) with b[j] < a[i].
Output line 2: the smallest |a[i] - b[j]| over all pairs.
Input: n m, then a[0..n-1], then b[0..m-1] (any order; n, m >= 1).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.5. For sorted a and b: the number of pairs (i, j) with b_j < a_i, and the smallest |a_i - b_j|.
pair<long long, long long> walkTwo(vector<long long> a, vector<long long> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int n = a.size(), m = b.size(), j = 0;  // j = number of b values less than a[i]
    long long pairs = 0, closest = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        while (j < m && b[j] < a[i]) j++;
        pairs += j;
        if (j < m) closest = min(closest, b[j] - a[i]);      // first b >= a[i]
        if (j > 0) closest = min(closest, a[i] - b[j - 1]);  // last b < a[i]
    }
    return {pairs, closest};
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);  // differences of values up to 10^9 reach 2*10^9
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    pair<long long, long long> r = walkTwo(a, b);
    cout << r.first << "\n" << r.second << "\n";
}
