#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.3.4. Add x to the states l..r, maximum of the states l..r: O(log n) each. The add at a node is not pushed down.
struct AddMax {
    vector<long long> mx, add;
    AddMax(int n) : mx(4 * n, 0), add(4 * n, 0) {}
    void update(int v, int lo, int hi, int l, int r, long long x) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) { mx[v] += x, add[v] += x; return; }
        int mid = (lo + hi) / 2;
        update(2 * v, lo, mid, l, r, x), update(2 * v + 1, mid + 1, hi, l, r, x);
        mx[v] = max(mx[2 * v], mx[2 * v + 1]) + add[v];
    }
    long long query(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return LLONG_MIN / 2;
        if (l <= lo && hi <= r) return mx[v];
        int mid = (lo + hi) / 2;
        return max(query(2 * v, lo, mid, l, r), query(2 * v + 1, mid + 1, hi, l, r)) + add[v];
    }
};
// State j = the position of the last 1 so far (0: none). A 1 at i starts the state i from the best state before it; an interval
// (l, r, a) with r = i adds a to the states l..i. Returns the tree of the states 0..n.
AddMax bestIntervals(int n, vector<array<long long, 3>> iv) {
    sort(iv.begin(), iv.end(), [](auto& x, auto& y) { return x[1] < y[1]; });
    AddMax f(n + 1);
    size_t p = 0;
    for (int i = 1; i <= n; i++) {
        f.update(1, 0, n, i, i, f.query(1, 0, n, 0, i - 1));
        for (; p < iv.size() && iv[p][1] == i; p++) f.update(1, 0, n, iv[p][0], i, iv[p][2]);
    }
    return f;
}
// snippet:end

long long bruteIntervals(int n, const vector<array<long long, 3>>& intervals) {
    long long best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long total = 0;
        for (auto [l, r, a] : intervals)
            if (mask >> (l - 1) & ((1 << (r - l + 1)) - 1)) total += a;
        best = max(best, total);
    }
    return best;
}

int main() {
    vector<array<long long, 3>> iv = {{1, 2, 10}, {2, 3, -5}, {3, 3, 20}};
    auto f = bestIntervals(3, iv);
    cout << "f:";
    for (int j = 0; j <= 3; j++) cout << " " << f.query(1, 0, 3, j, j);
    cout << "\nmost: " << f.query(1, 0, 3, 0, 3) << "\n";
    // Check (not printed): 3000 random cases of up to 9 positions and 9 intervals (rewards from -5 to 10), against all 2^n strings.
    mt19937 rng(14);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 9 + 1, m = rng() % 9 + 1;
        vector<array<long long, 3>> v;
        for (int i = 0; i < m; i++) {
            int l = rng() % n + 1, r = rng() % n + 1;
            if (l > r) swap(l, r);
            v.push_back({l, r, (long long)(rng() % 16) - 5});
        }
        auto g = bestIntervals(n, v);
        if (g.query(1, 0, n, 0, n) != bruteIntervals(n, v)) return 1;
    }
}
