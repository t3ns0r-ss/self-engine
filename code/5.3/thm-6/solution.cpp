#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.6. The node keeps four numbers for its range; the best sum of a (non-empty) subarray inside it is `best`.
struct Node {
    long long sum, pref, suf, best;  // total, best prefix, best suffix, best subarray
};
Node combine(const Node& a, const Node& b) {  // a is the left part, b the right part: the order matters
    return {a.sum + b.sum, max(a.pref, a.sum + b.pref), max(b.suf, b.sum + a.suf), max({a.best, b.best, a.suf + b.pref})};
}
struct SubTree {
    int n;
    vector<Node> t;
    SubTree(const vector<long long>& a) : n(a.size()), t(4 * a.size()) { build(1, 0, n - 1, a); }
    void build(int v, int lo, int hi, const vector<long long>& a) {
        if (lo == hi) {
            t[v] = {a[lo], a[lo], a[lo], a[lo]};
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);
        build(2 * v + 1, mid + 1, hi, a);
        t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
    Node query(int v, int lo, int hi, int l, int r) const {  // l..r must overlap lo..hi
        if (l <= lo && hi <= r) return t[v];
        int mid = (lo + hi) / 2;
        if (r <= mid) return query(2 * v, lo, mid, l, r);
        if (l > mid) return query(2 * v + 1, mid + 1, hi, l, r);
        return combine(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
// snippet:end

int main() {
    vector<long long> a = {-1, 2, 3, -4, 5, -2};
    SubTree s(a);
    Node root = s.t[1];
    cout << "whole: sum " << root.sum << ", prefix " << root.pref << ", suffix " << root.suf << ", best " << root.best << "\n";
    cout << "best in [0..3] = " << s.query(1, 0, 5, 0, 3).best << ", best in [3..5] = " << s.query(1, 0, 5, 3, 5).best << "\n";
    // Check against: the best subarray by trying all of them, for every range of random arrays up to n = 14.
    mt19937 rng(3);
    for (int n = 1; n <= 14; n++)
        for (int round = 0; round < 100; round++) {
            vector<long long> b(n);
            for (auto& x : b) x = (long long)(rng() % 15) - 7;
            SubTree t(b);
            for (int l = 0; l < n; l++)
                for (int r = l; r < n; r++) {
                    long long want = LLONG_MIN;
                    for (int i = l; i <= r; i++) {
                        long long sum = 0;
                        for (int j = i; j <= r; j++) {
                            sum += b[j];
                            want = max(want, sum);
                        }
                    }
                    if (t.query(1, 0, n - 1, l, r).best != want) return 1;
                }
        }
}
