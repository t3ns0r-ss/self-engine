#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.3. A tree over the positions 0 .. m-1 (all values 0 at the start) with add(l, r, d) on positions l .. r-1,
// the maximum value, and the leftmost position that holds it. Nothing is pushed down.
struct MaxTree {
    int m;
    vector<long long> best;  // best[v]: the maximum over the node of what was added at the node or below it
    vector<long long> here;  // here[v]: what was added to the whole node
    MaxTree(int m) : m(m), best(4 * m), here(4 * m) {}
    void add(int v, int lo, int hi, int l, int r, long long d) {  // the node covers positions lo .. hi-1
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) {
            here[v] += d, best[v] += d;
            return;
        }
        int mid = (lo + hi) / 2;
        add(2 * v, lo, mid, l, r, d), add(2 * v + 1, mid, hi, l, r, d);
        best[v] = here[v] + max(best[2 * v], best[2 * v + 1]);
    }
    void add(int l, int r, long long d) { add(1, 0, m, l, r, d); }
    long long maximum() const { return best[1]; }
    int leftmostMaximum() const {
        int v = 1, lo = 0, hi = m;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (best[2 * v] == best[v] - here[v]) v = 2 * v, hi = mid;  // the left child reaches the maximum
            else v = 2 * v + 1, lo = mid;
        }
        return lo;
    }
};
// snippet:end

int main() {
    {
        MaxTree t(8);
        t.add(0, 4, 1), t.add(2, 6, 1), t.add(3, 5, 1);
        cout << "add 1 to [0,4), [2,6), [3,5) on positions 0..7: maximum " << t.maximum() << " at position " << t.leftmostMaximum() << "\n";
    }
    {
        MaxTree t(8);
        t.add(0, 2, 5), t.add(4, 6, 5);
        cout << "add 5 to [0,2) and to [4,6): maximum " << t.maximum() << " at position " << t.leftmostMaximum() << "\n";
    }
    {
        MaxTree t(3);
        t.add(0, 3, 4), t.add(0, 3, -4);
        cout << "add 4 to [0,3), then add -4 to [0,3): maximum " << t.maximum() << " at position " << t.leftmostMaximum() << "\n";
    }
    // Check against a plain array on random sequences with positive and negative additions.
    mt19937 rng(777);
    for (int round = 0; round < 4000; round++) {
        int m = rng() % 9 + 1;
        MaxTree tree(m);
        vector<long long> plain(m, 0);
        for (int step = 0; step < 25; step++) {
            int l = rng() % m, r = l + 1 + rng() % (m - l);
            long long d = (long long)(rng() % 11) - 5;
            tree.add(l, r, d);
            for (int g = l; g < r; g++) plain[g] += d;
            long long best = *max_element(plain.begin(), plain.end());
            int first = max_element(plain.begin(), plain.end()) - plain.begin();  // the first maximum is the leftmost
            if (tree.maximum() != best || tree.leftmostMaximum() != first) return 1;
        }
    }
}
