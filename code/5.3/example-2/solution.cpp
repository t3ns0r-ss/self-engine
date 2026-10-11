#include <bits/stdc++.h>
using namespace std;

/*
Problem (Codeforces 52C, Circular RMQ): a circle of n numbers (0-based places); m operations: "lf rg" asks for the minimum on the circular
range from lf to rg, "lf rg v" adds v to every number on it. If lf > rg the range goes from lf to n-1 and then from 0 to rg.
Input: n, the n numbers, m, then m lines with two or three numbers.
Output: the answer to each question of the first kind.
*/

// snippet:begin
// Range add and range minimum with lazy tags. t[v] is the minimum of the node's range, tag[v] an addition the children have not got yet.
struct LazyMin {
    int n;
    vector<long long> t, tag;
    LazyMin(const vector<long long>& a) : n(a.size()), t(4 * a.size(), 0), tag(4 * a.size(), 0) {
        for (int i = 0; i < n; i++) add(1, 0, n - 1, i, i, a[i]);  // start from zeros and add each value to its own place
    }
    void apply(int v, long long d) { t[v] += d, tag[v] += d; }  // a minimum rises by d, whatever the length
    void push(int v) {
        apply(2 * v, tag[v]), apply(2 * v + 1, tag[v]);
        tag[v] = 0;
    }
    void add(int v, int lo, int hi, int l, int r, long long d) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, d);
        push(v);
        int mid = (lo + hi) / 2;
        add(2 * v, lo, mid, l, r, d);
        add(2 * v + 1, mid + 1, hi, l, r, d);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    long long query(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return LLONG_MAX;
        if (l <= lo && hi <= r) return t[v];
        push(v);
        int mid = (lo + hi) / 2;
        return min(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
// snippet:end

int main() {
    int n, m;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    LazyMin tree(a);
    cin >> m;
    string line;
    getline(cin, line);
    while (m--) {
        getline(cin, line);
        istringstream in(line);
        long long lf, rg, v;
        in >> lf >> rg;
        bool inc = static_cast<bool>(in >> v);
        vector<array<int, 2>> parts;
        if (lf <= rg) parts = {{(int)lf, (int)rg}};
        else parts = {{(int)lf, n - 1}, {0, (int)rg}};
        long long best = LLONG_MAX;
        for (auto [l, r] : parts) {
            if (inc) tree.add(1, 0, n - 1, l, r, v);
            else best = min(best, tree.query(1, 0, n - 1, l, r));
        }
        if (!inc) cout << best << "\n";
    }
}
