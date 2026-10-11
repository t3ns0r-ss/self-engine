#include <bits/stdc++.h>
using namespace std;

/*
Problem: n product prices; q operations: "1 k x" sets the price of product k to x, "2 a b" asks for the lowest price among products a..b.
Input: n q, the n prices, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Point set and range minimum on positions 0..n-1: node v covers lo..hi and holds the minimum of that range.
struct MinTree {
    int n;
    vector<long long> t;
    MinTree(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    void set(int v, int lo, int hi, int i, long long x) {
        if (lo == hi) {
            t[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) set(2 * v, lo, mid, i, x);
        else set(2 * v + 1, mid + 1, hi, i, x);
        t[v] = min(t[2 * v], t[2 * v + 1]);  // recompute on the way back up
    }
    long long query(int v, int lo, int hi, int l, int r) const {
        if (r < lo || hi < l) return LLONG_MAX;  // disjoint: the neutral element of min
        if (l <= lo && hi <= r) return t[v];
        int mid = (lo + hi) / 2;
        return min(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    MinTree tree(a);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long x;
            cin >> k >> x;
            tree.set(1, 0, n - 1, k - 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tree.query(1, 0, n - 1, l - 1, r - 1) << "\n";
        }
    }
}
