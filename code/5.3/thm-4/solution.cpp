#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.4. A tag is a map x -> mul * x + add: add c is (1, c), assign c is (0, c); (m, c) after (M, A) is (m * M, m * A + c).
struct LazyAffine {
    vector<long long> t, mul, add;  // t: sums; (mul, add): the pending tag of each node
    LazyAffine(int size) : t(4 * size, 0), mul(4 * size, 1), add(4 * size, 0) {}  // all values start at 0
    void apply(int v, int lo, int hi, long long m, long long c) {  // the new map acts after the old one
        t[v] = m * t[v] + c * (hi - lo + 1), mul[v] *= m, add[v] = m * add[v] + c;
    }
    void push(int v, int lo, int hi) {
        int mid = (lo + hi) / 2;
        apply(2 * v, lo, mid, mul[v], add[v]);
        apply(2 * v + 1, mid + 1, hi, mul[v], add[v]);
        mul[v] = 1, add[v] = 0;
    }
    void update(int v, int lo, int hi, int l, int r, long long m, long long c) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, lo, hi, m, c);
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        update(2 * v, lo, mid, l, r, m, c);
        update(2 * v + 1, mid + 1, hi, l, r, m, c);
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
    vector<long long> a = {3, 1, 4, 1};
    LazyAffine s(4);
    for (int i = 0; i < 4; i++) s.update(1, 0, 3, i, i, 0, a[i]);  // assign each value to its own place
    s.update(1, 0, 3, 0, 3, 1, 2);  // add 2 to all
    s.update(1, 0, 3, 0, 3, 3, 0);  // then multiply by 3
    cout << "(+2) then (*3): sum = " << s.query(1, 0, 3, 0, 3) << "\n";
    LazyAffine u(4);
    for (int i = 0; i < 4; i++) u.update(1, 0, 3, i, i, 0, a[i]);
    u.update(1, 0, 3, 0, 3, 3, 0);  // multiply by 3
    u.update(1, 0, 3, 0, 3, 1, 2);  // then add 2
    cout << "(*3) then (+2): sum = " << u.query(1, 0, 3, 0, 3) << "\n";
    LazyAffine w(4);
    for (int i = 0; i < 4; i++) w.update(1, 0, 3, i, i, 0, a[i]);
    w.update(1, 0, 3, 1, 2, 0, 7);  // assign 7 to positions 1..2
    cout << "assign 7 to [1..2]: sum = " << w.query(1, 0, 3, 0, 3) << ", sum[2..3] = " << w.query(1, 0, 3, 2, 3) << "\n";
    // Check against: a plain array, on random assign / add / multiply operations for every n up to 12.
    mt19937 rng(11);
    for (int n = 1; n <= 12; n++)
        for (int round = 0; round < 300; round++) {
            vector<long long> b(n);
            for (auto& x : b) x = rng() % 4;
            LazyAffine t(n);
            for (int i = 0; i < n; i++) t.update(1, 0, n - 1, i, i, 0, b[i]);
            for (int op = 0; op < 8; op++) {
                int l = rng() % n, r = rng() % n;
                if (l > r) swap(l, r);
                int kind = rng() % 4;
                if (kind == 3) {
                    long long want = 0;
                    for (int i = l; i <= r; i++) want += b[i];
                    if (t.query(1, 0, n - 1, l, r) != want) return 1;
                    continue;
                }
                long long c = rng() % 3 + 1;
                long long m = kind == 2 ? c : kind == 1 ? 0 : 1, add = kind == 2 ? 0 : c;
                t.update(1, 0, n - 1, l, r, m, add);
                for (int i = l; i <= r; i++) b[i] = m * b[i] + add;
            }
        }
}
