#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum, pref, suf, best;
};
Node combine(const Node& a, const Node& b) {
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
    Node query(int v, int lo, int hi, int l, int r) const {
        if (l <= lo && hi <= r) return t[v];
        int mid = (lo + hi) / 2;
        if (r <= mid) return query(2 * v, lo, mid, l, r);
        if (l > mid) return query(2 * v + 1, mid + 1, hi, l, r);
        return combine(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r));
    }
};
long long bruteBest(const vector<long long>& a, int l, int r) {
    long long best = LLONG_MIN;
    for (int i = l; i <= r; i++) {
        long long s = 0;
        for (int j = i; j <= r; j++) s += a[j], best = max(best, s);
    }
    return best;
}
// N1 helper: the number of different values, joined by adding the numbers of the two halves.
int distinctByHalves(const vector<int>& a, int lo, int hi) {
    if (lo == hi) return 1;
    int mid = (lo + hi) / 2;
    return distinctByHalves(a, lo, mid) + distinctByHalves(a, mid + 1, hi);
}

int main() {
    {
        vector<long long> a = {-1, 2, 3, -4, 5, -2};
        SubTree s(a);
        cout << "P1 brute=" << bruteBest(a, 1, 4) << " method=" << s.query(1, 0, 5, 1, 4).best << "\n";
    }
    {
        vector<long long> a = {4, -10, 3, -1, 3};
        SubTree s(a);
        cout << "P2 brute=" << bruteBest(a, 1, 4) << " method=" << s.query(1, 0, 4, 1, 4).best << "\n";
    }
    {
        vector<int> a = {1, 2, 1, 2};
        set<int> d(a.begin(), a.end());
        cout << "N1 brute=" << d.size() << " method=" << distinctByHalves(a, 0, 3) << "\n";
    }
}
