#include <bits/stdc++.h>
using namespace std;

/*
Problem (Codeforces 1676H2, Maximum Crossings, hard): several tests; n numbers a_1..a_n with 1 <= a_i <= n.
Count the pairs i < j with a_i >= a_j (the crossings).
Input: t, then for each test n and the n numbers.
Output: one number per test.
*/

// snippet:begin
// Pairs i < j with a[i] >= a[j], for values in 1..n: a Fenwick tree of counts over the values.
long long crossings(const vector<int>& a) {
    int n = a.size();
    vector<int> tree(n + 1, 0);  // tree over values: how many earlier numbers have each value
    long long total = 0;         // up to n(n-1)/2, about 2*10^10
    for (int j = 0; j < n; j++) {
        int smaller = 0;
        for (int v = a[j] - 1; v > 0; v -= v & -v) smaller += tree[v];  // earlier numbers below a[j]
        total += j - smaller;  // the other j - smaller earlier numbers are >= a[j]
        for (int v = a[j]; v <= n; v += v & -v) tree[v]++;
    }
    return total;
}
// snippet:end

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        cout << crossings(a) << "\n";
    }
}
