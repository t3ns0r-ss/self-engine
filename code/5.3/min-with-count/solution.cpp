#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q operations: "1 k x" sets a_k = x, "2 a b" asks for the smallest value among a..b and how many times it occurs there.
Input: n q, the n numbers, then q operations (1-based).
Output: for each operation of the second kind, the smallest value and its count, separated by a space.
*/

// snippet:begin
// A node keeps two numbers: the minimum of its range and how many times it occurs. Joining adds the counts when the minimums tie.
struct Node {
    long long mn;
    int cnt;
};
Node join(const Node& a, const Node& b) {
    if (a.mn != b.mn) return a.mn < b.mn ? a : b;
    return {a.mn, a.cnt + b.cnt};
}
struct CountTree {
    int n;
    vector<Node> t;
    CountTree(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = {a[lo], 1};
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = join(t[2 * v], t[2 * v + 1]);
    }
    void set(int v, int lo, int hi, int i, long long x) {
        if (lo == hi) {
            t[v] = {x, 1};
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) set(2 * v, lo, mid, i, x);
        else set(2 * v + 1, mid + 1, hi, i, x);
        t[v] = join(t[2 * v], t[2 * v + 1]);
    }
    Node query(int v, int lo, int hi, int l, int r) const {
        if (r < lo || hi < l) return {LLONG_MAX, 0};  // disjoint: no values at all
        if (l <= lo && hi <= r) return t[v];
        int mid = (lo + hi) / 2;
        return join(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    CountTree tree(a);
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
            Node res = tree.query(1, 0, n - 1, l - 1, r - 1);
            cout << res.mn << " " << res.cnt << "\n";
        }
    }
}
