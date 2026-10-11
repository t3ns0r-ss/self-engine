#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q operations: "1 l r x" sets every number in l..r to x, "2 l r" asks for the sum of l..r.
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Range assign and range sum. has[v] says that the whole node was assigned the value val[v] and the children do not know yet.
struct AssignSum {
    int n;
    vector<long long> t, val;
    vector<char> has;
    AssignSum(const vector<long long>& a) : n(a.size()), t(4 * a.size()), val(4 * a.size(), 0), has(4 * a.size(), 0) { build(1, 0, n - 1, a); }
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
    void apply(int v, int lo, int hi, long long x) {
        t[v] = x * (hi - lo + 1);
        val[v] = x;
        has[v] = 1;  // a flag, because the assigned value may itself be 0
    }
    void push(int v, int lo, int hi) {
        if (!has[v]) return;
        int mid = (lo + hi) / 2;
        apply(2 * v, lo, mid, val[v]);
        apply(2 * v + 1, mid + 1, hi, val[v]);
        has[v] = 0;
    }
    void assign(int v, int lo, int hi, int l, int r, long long x) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) return apply(v, lo, hi, x);
        push(v, lo, hi);
        int mid = (lo + hi) / 2;
        assign(2 * v, lo, mid, l, r, x);
        assign(2 * v + 1, mid + 1, hi, l, r, x);
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
    AssignSum tree(a);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long x;
            cin >> x;
            tree.assign(1, 0, n - 1, l - 1, r - 1, x);
        } else {
            cout << tree.sum(1, 0, n - 1, l - 1, r - 1) << "\n";
        }
    }
}
