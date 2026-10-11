#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q changes "k x" set a_k = x. After each change print the largest sum of a subarray (the empty subarray counts, sum 0).
Input: n q, the n numbers, then q lines k x (1-based).
Output: one line per change.
*/

// snippet:begin
// A node keeps four numbers for its range; the empty subarray is allowed, so every value is at least 0.
struct Node {
    long long sum, pref, suf, best;
};
Node join(const Node& a, const Node& b) {  // a is the left part, b the right part
    return {a.sum + b.sum, max(a.pref, a.sum + b.pref), max(b.suf, b.sum + a.suf), max({a.best, b.best, a.suf + b.pref})};
}
Node leaf(long long x) {
    long long p = max(0LL, x);
    return {x, p, p, p};
}
struct BestTree {
    int n;
    vector<Node> t;
    BestTree(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = leaf(a[lo]);
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = join(t[2 * v], t[2 * v + 1]);
    }
    void set(int v, int lo, int hi, int i, long long x) {
        if (lo == hi) {
            t[v] = leaf(x);
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) set(2 * v, lo, mid, i, x);
        else set(2 * v + 1, mid + 1, hi, i, x);
        t[v] = join(t[2 * v], t[2 * v + 1]);
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    BestTree tree(a);
    while (q--) {
        int k;
        long long x;
        cin >> k >> x;
        tree.set(1, 0, n - 1, k - 1, x);
        cout << tree.t[1].best << "\n";
    }
}
