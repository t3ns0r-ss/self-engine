#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.2. Set a[i] = x: change the leaf, then recompute only the nodes on the way back up.
struct SegTree {
    int n;
    vector<long long> t;
    SegTree(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
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
    void update(int v, int lo, int hi, int i, long long x) {
        if (lo == hi) {
            t[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) update(2 * v, lo, mid, i, x);
        else update(2 * v + 1, mid + 1, hi, i, x);
        t[v] = t[2 * v] + t[2 * v + 1];  // only the nodes that contain position i are recomputed
    }
};
// snippet:end

int main() {
    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    SegTree s(a);
    vector<long long> before = s.t;
    s.update(1, 0, 7, 2, 10);
    cout << "changed nodes:";
    for (size_t v = 1; v < s.t.size(); v++)
        if (s.t[v] != before[v]) cout << ' ' << v;
    cout << "\n";
    cout << "root = " << s.t[1] << "\n";
    // Check against: a tree rebuilt from the changed array (no other node differs), for every n up to 33 and every position.
    for (int n = 1; n <= 33; n++) {
        vector<long long> b(n);
        for (int i = 0; i < n; i++) b[i] = (i * 5 + 1) % 7;
        for (int i = 0; i < n; i++) {
            SegTree x(b);
            x.update(1, 0, n - 1, i, 100);
            vector<long long> c = b;
            c[i] = 100;
            SegTree y(c);
            for (size_t v = 1; v < x.t.size(); v++) {
                bool used = v < 4 * (size_t)n && (v == 1 || x.t[v] != 0 || y.t[v] != 0);
                if (used && x.t[v] != y.t[v]) return 1;
            }
        }
    }
}
