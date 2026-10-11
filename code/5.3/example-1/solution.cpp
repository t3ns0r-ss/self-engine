#include <bits/stdc++.h>
using namespace std;

/*
Problem (CSES 1649, Dynamic Range Minimum Queries): n numbers; q operations: "1 k u" sets a_k = u, "2 a b" asks for the minimum of a_a..a_b (1-based).
Input: n q, the n numbers, then q operations.
Output: the answer to each question of the second kind.
*/

// snippet:begin
// Point set and range minimum: node v covers lo..hi (0-based) and holds the minimum of that range.
struct MinTree {
    int n;
    vector<int> t;
    MinTree(const vector<int>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<int>& a) {
        if (lo == hi) return void(t[v] = a[lo]);
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    void set(int v, int lo, int hi, int i, int x) {
        if (lo == hi) return void(t[v] = x);
        int mid = (lo + hi) / 2;
        if (i <= mid) set(2 * v, lo, mid, i, x);
        else set(2 * v + 1, mid + 1, hi, i, x);
        t[v] = min(t[2 * v], t[2 * v + 1]);  // fix the nodes above the changed leaf
    }
    int query(int v, int lo, int hi, int l, int r) const {
        if (r < lo || hi < l) return INT_MAX;  // outside: the neutral element of min
        if (l <= lo && hi <= r) return t[v];   // inside: the stored minimum
        int mid = (lo + hi) / 2;
        return min(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    MinTree tree(a);
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) tree.set(1, 0, n - 1, x - 1, y);
        else cout << tree.query(1, 0, n - 1, x - 1, y - 1) << "\n";
    }
}
