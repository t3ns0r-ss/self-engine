#include <bits/stdc++.h>
using namespace std;

/*
Problem: n lamps with brightness a_i; q operations: "1 l r d" adds d to the brightness of lamps l..r, "2 l r" asks for the total brightness of lamps l..r.
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Range add and range sum. t[v] is the sum of the node's range with all additions aimed at it counted;
// tag[v] is an addition not yet handed to the children.
struct LazySum {
    int n;
    vector<long long> t, tag;
    LazySum(const vector<long long>& a) : n(a.size()), t(4 * a.size()), tag(4 * a.size(), 0) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    void apply(int v, int lo, int hi, long long d) {
        t[v] += d * (hi - lo + 1);
        tag[v] += d;
    }
    void push(int v, int lo, int hi) {
        if (tag[v] == 0) return;
        int mid = (lo + hi) / 2;
        apply(2 * v, lo, mid, tag[v]);
        apply(2 * v + 1, mid + 1, hi, tag[v]);
        tag[v] = 0;
    }
    void add(int v, int lo, int hi, int l, int r, long long d) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, lo, hi, d);
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        add(2 * v, lo, mid, l, r, d);
        add(2 * v + 1, mid + 1, hi, l, r, d);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    long long sum(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) return t[v];
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        return sum(2 * v, lo, mid, l, r) + sum(2 * v + 1, mid + 1, hi, l, r);
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    LazySum tree(a);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long d;
            cin >> d;
            tree.add(1, 0, n - 1, l - 1, r - 1, d);
        } else {
            cout << tree.sum(1, 0, n - 1, l - 1, r - 1) << "\n";
        }
    }
}
