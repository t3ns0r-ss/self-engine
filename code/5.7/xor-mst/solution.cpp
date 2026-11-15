#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers below 2^30. Between every two of them there is an edge whose weight is their XOR. Print the weight of a
cheapest spanning tree.
Input: n, then the n numbers.
Output: the weight.
*/

// snippet:begin
// Theorem 5.7.3. The numbers a[lo, hi) (sorted, distinct) agree on every digit above b.
long long xorMst(const vector<int>& a, int lo, int hi, int b) {
    if (hi - lo <= 1 || b < 0) return 0;
    int mid = lo;
    while (mid < hi && !(a[mid] >> b & 1)) mid++;  // the split by the digit b: a[lo, mid) has 0, a[mid, hi) has 1
    if (mid == lo || mid == hi) return xorMst(a, lo, hi, b - 1);
    vector<array<int, 2>> child(1);  // a trie of the right part below the digit b
    for (int i = mid; i < hi; i++) {
        int v = 0;
        for (int c = b - 1; c >= 0; c--) {
            int d = a[i] >> c & 1;
            if (!child[v][d]) child[v][d] = child.size(), child.push_back({0, 0});
            v = child[v][d];
        }
    }
    long long cheapest = LLONG_MAX;
    for (int i = lo; i < mid; i++) {  // the cheapest edge across: the same digit whenever the trie has it
        int v = 0, x = 1 << b;
        for (int c = b - 1; c >= 0; c--) {
            int d = a[i] >> c & 1;
            if (!child[v][d]) d ^= 1, x |= 1 << c;
            v = child[v][d];
        }
        cheapest = min<long long>(cheapest, x);
    }
    return xorMst(a, lo, mid, b - 1) + xorMst(a, mid, hi, b - 1) + cheapest;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    cout << xorMst(a, 0, a.size(), 29) << "\n";
}
