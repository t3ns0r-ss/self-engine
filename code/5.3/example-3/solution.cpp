#include <bits/stdc++.h>
using namespace std;

/*
Problem (CSES 1190, Subarray Sum Queries): n numbers; m changes "k x" set a_k = x (1-based). After each change print the largest sum of a
subarray (the empty subarray is allowed, so the answer is at least 0).
Input: n m, the n numbers, then m lines k x.
Output: m lines.
*/

// snippet:begin
// Each node keeps (sum, best prefix, best suffix, best subarray) of its range; empty parts are allowed, so the last three are >= 0.
struct Node {
    long long sum, pref, suf, best;
};
Node join(const Node& a, const Node& b) {  // a is the left part, b the right part
    return {a.sum + b.sum, max(a.pref, a.sum + b.pref), max(b.suf, b.sum + a.suf), max({a.best, b.best, a.suf + b.pref})};
}
Node leaf(long long x) { return {x, max(0LL, x), max(0LL, x), max(0LL, x)}; }
vector<Node> t;  // t[v] for the node v covering lo..hi
void build(int v, int lo, int hi, const vector<long long>& a) {
    if (lo == hi) return void(t[v] = leaf(a[lo]));
    int mid = (lo + hi) / 2;
    build(2 * v, lo, mid, a);
    build(2 * v + 1, mid + 1, hi, a);
    t[v] = join(t[2 * v], t[2 * v + 1]);
}
void change(int v, int lo, int hi, int i, long long x) {
    if (lo == hi) return void(t[v] = leaf(x));
    int mid = (lo + hi) / 2;
    if (i <= mid) change(2 * v, lo, mid, i, x);
    else change(2 * v + 1, mid + 1, hi, i, x);
    t[v] = join(t[2 * v], t[2 * v + 1]);
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    t.assign(4 * n, Node());
    build(1, 0, n - 1, a);
    while (m--) {
        int k;
        long long x;
        cin >> k >> x;
        change(1, 0, n - 1, k - 1, x);
        cout << t[1].best << "\n";
    }
}
