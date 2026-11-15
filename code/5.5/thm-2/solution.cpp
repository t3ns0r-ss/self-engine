#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.5.2. A counted-cover tree over the gaps 0 .. m-1; gap g has length width[g].
// add(l, r, d) adds d (+1 or -1) to the gaps l .. r-1; covered() is the total length of the gaps with a positive count.
struct CoverTree {
    int m;
    vector<int> count;               // intervals placed exactly at this node (never pushed down)
    vector<long long> whole, inside;  // whole length of the node; covered length by intervals at or below the node
    CoverTree(const vector<long long>& width) : m(width.size()), count(4 * m), whole(4 * m), inside(4 * m) { build(1, 0, m, width); }
    void build(int v, int lo, int hi, const vector<long long>& width) {  // the node covers gaps lo .. hi-1
        if (hi - lo == 1) { whole[v] = width[lo]; return; }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, width), build(2 * v + 1, mid, hi, width);
        whole[v] = whole[2 * v] + whole[2 * v + 1];
    }
    void add(int v, int lo, int hi, int l, int r, int d) {
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) count[v] += d;  // the interval is placed here
        else add(2 * v, lo, (lo + hi) / 2, l, r, d), add(2 * v + 1, (lo + hi) / 2, hi, l, r, d);
        inside[v] = count[v] > 0 ? whole[v] : (hi - lo == 1 ? 0 : inside[2 * v] + inside[2 * v + 1]);
    }
    void add(int l, int r, int d) { add(1, 0, m, l, r, d); }
    long long covered() const { return inside[1]; }
};
// snippet:end

int main() {
    // Gap widths 1, 2, 3, 4 (total 10).
    CoverTree t({1, 2, 3, 4});
    cout << "gap widths 1, 2, 3, 4 (covered length after each change)\n";
    t.add(0, 2, +1);
    cout << "add gaps 0-1: " << t.covered() << "\n";
    t.add(1, 3, +1);
    cout << "then add gaps 1-2: " << t.covered() << "\n";
    t.add(0, 2, -1);
    cout << "then remove gaps 0-1: " << t.covered() << "\n";
    t.add(1, 3, -1);
    cout << "then remove gaps 1-2: " << t.covered() << "\n";
    // Check against a plain count per gap on random sequences; a removal repeats an earlier interval.
    mt19937 rng(12345);
    for (int round = 0; round < 3000; round++) {
        int m = rng() % 7 + 1;
        vector<long long> width(m);
        for (auto& w : width) w = rng() % 5 + 1;
        CoverTree tree(width);
        vector<int> plain(m, 0);
        vector<pair<int, int>> active;
        for (int step = 0; step < 30; step++) {
            if (!active.empty() && rng() % 3 == 0) {
                int k = rng() % active.size();
                auto [l, r] = active[k];
                active.erase(active.begin() + k);
                tree.add(l, r, -1);
                for (int g = l; g < r; g++) plain[g]--;
            } else {
                int l = rng() % m, r = l + 1 + rng() % (m - l);
                active.push_back({l, r});
                tree.add(l, r, +1);
                for (int g = l; g < r; g++) plain[g]++;
            }
            long long want = 0;
            for (int g = 0; g < m; g++)
                if (plain[g] > 0) want += width[g];
            if (tree.covered() != want) return 1;
        }
    }
}
