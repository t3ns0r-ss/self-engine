#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.3. Add x to a[l..r], ask for sums. tag[v]: an addition counted in t[v] that the children have not received.
struct LazySum {
    int n;
    vector<long long> t, tag;
    LazySum(int size) : n(size), t(4 * size, 0), tag(4 * size, 0) {}  // all values start at 0
    void apply(int v, int lo, int hi, long long x) { t[v] += x * (hi - lo + 1), tag[v] += x; }  // add x to the whole node
    void push(int v, int lo, int hi) {  // hand the pending addition down to both children
        int mid = (lo + hi) / 2;
        apply(2 * v, lo, mid, tag[v]);
        apply(2 * v + 1, mid + 1, hi, tag[v]);
        tag[v] = 0;
    }
    void update(int v, int lo, int hi, int l, int r, long long x) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, lo, hi, x);
        push(v, lo, hi);  // before looking at the children, bring them up to date
        int mid = (lo + hi) / 2;
        update(2 * v, lo, mid, l, r, x);
        update(2 * v + 1, mid + 1, hi, l, r, x);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    long long query(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) return t[v];
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        return query(2 * v, lo, mid, l, r) + query(2 * v + 1, mid + 1, hi, l, r);
    }
};
// snippet:end

int main() {
    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    LazySum s(8);
    for (int i = 0; i < 8; i++) s.update(1, 0, 7, i, i, a[i]);
    s.update(1, 0, 7, 2, 5, 10);
    cout << "after +10 on [2..5]: root = " << s.t[1] << ", sum[0..7] = " << s.query(1, 0, 7, 0, 7) << "\n";
    cout << "sum[3..4] = " << s.query(1, 0, 7, 3, 4) << ", sum[5..6] = " << s.query(1, 0, 7, 5, 6) << ", sum[0..1] = " << s.query(1, 0, 7, 0, 1) << "\n";
    s.update(1, 0, 7, 0, 7, -1);
    cout << "after -1 on everything: sum[0..7] = " << s.query(1, 0, 7, 0, 7) << "\n";
    // Check against: a plain array, on random operations for every n up to 20.
    mt19937 rng(7);
    for (int n = 1; n <= 20; n++)
        for (int round = 0; round < 200; round++) {
            vector<long long> b(n);
            for (auto& x : b) x = (long long)(rng() % 21) - 10;
            LazySum t(n);
            for (int i = 0; i < n; i++) t.update(1, 0, n - 1, i, i, b[i]);
            for (int op = 0; op < 30; op++) {
                int l = rng() % n, r = rng() % n;
                if (l > r) swap(l, r);
                if (rng() % 2) {
                    long long x = (long long)(rng() % 21) - 10;
                    t.update(1, 0, n - 1, l, r, x);
                    for (int i = l; i <= r; i++) b[i] += x;
                } else {
                    long long want = 0;
                    for (int i = l; i <= r; i++) want += b[i];
                    if (t.query(1, 0, n - 1, l, r) != want) return 1;
                }
            }
        }
}
