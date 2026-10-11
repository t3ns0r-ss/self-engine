#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.3.1. Node v covers positions lo..hi (0-based); t[v] = the sum of a over that range; its children are 2v and 2v+1.
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
        t[v] = t[2 * v] + t[2 * v + 1];  // the node is the sum of its two halves
    }
    long long query(int v, int lo, int hi, int l, int r) const {  // the sum of a[l..r]
        if (r < lo || hi < l) return 0;       // the node and the range share nothing
        if (l <= lo && hi <= r) return t[v];  // the node lies inside the range: take it whole
        int mid = (lo + hi) / 2;
        return query(2 * v, lo, mid, l, r) + query(2 * v + 1, mid + 1, hi, l, r);
    }
};
// snippet:end

// For the check only: the nodes a query takes whole, and the nodes it visits.
static void walk(int v, int lo, int hi, int l, int r, vector<array<int, 2>>& whole, int& visited, vector<int>& perLevel, int depth) {
    visited++;
    if ((int)perLevel.size() <= depth) perLevel.resize(depth + 1, 0);
    perLevel[depth]++;
    if (r < lo || hi < l) return;
    if (l <= lo && hi <= r) {
        whole.push_back({lo, hi});
        return;
    }
    int mid = (lo + hi) / 2;
    walk(2 * v, lo, mid, l, r, whole, visited, perLevel, depth + 1);
    walk(2 * v + 1, mid + 1, hi, l, r, whole, visited, perLevel, depth + 1);
}

int main() {
    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    SegTree s(a);
    cout << "root = " << s.t[1] << ", left half = " << s.t[2] << ", right half = " << s.t[3] << "\n";
    for (auto [l, r] : vector<array<int, 2>>{{2, 6}, {0, 7}, {5, 5}}) {
        vector<array<int, 2>> whole;
        vector<int> perLevel;
        int visited = 0;
        walk(1, 0, 7, l, r, whole, visited, perLevel, 0);
        cout << "sum[" << l << ".." << r << "] = " << s.query(1, 0, 7, l, r) << " from the nodes";
        for (auto [x, y] : whole) cout << " [" << x << ".." << y << "]";
        cout << "\n";
    }
    // Check against: the plain sum for every range, and at most 4 visited nodes per level, for every n up to 40.
    for (int n = 1; n <= 40; n++) {
        vector<long long> b(n);
        for (int i = 0; i < n; i++) b[i] = (i * 7 + 3) % 11 - 5;
        SegTree t(b);
        int levels = 1;
        while ((1 << (levels - 1)) < n) levels++;
        for (int l = 0; l < n; l++)
            for (int r = l; r < n; r++) {
                long long want = 0;
                for (int i = l; i <= r; i++) want += b[i];
                if (t.query(1, 0, n - 1, l, r) != want) return 1;
                vector<array<int, 2>> whole;
                vector<int> perLevel;
                int visited = 0;
                walk(1, 0, n - 1, l, r, whole, visited, perLevel, 0);
                for (int c : perLevel)
                    if (c > 4) return 1;
                if ((int)perLevel.size() > levels + 1) return 1;
            }
    }
}
