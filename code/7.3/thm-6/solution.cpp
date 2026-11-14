#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

// snippet:begin
// Theorem 7.3.6. A tree over the points 0..size-1; each node keeps one line, the one lower at the middle of its range.
// The other line can be lower on one side of the middle only, so it goes down into that child and nowhere else.
struct LiChao {
    int size;
    vector<long long> slope, icpt;  // slope 0 and intercept INF means "no line yet"
    LiChao(int size) : size(size), slope(4 * size, 0), icpt(4 * size, INF) {}
    long long at(int node, long long x) const { return slope[node] * x + icpt[node]; }
    void add(long long m, long long c) {
        int node = 1, lo = 0, hi = size - 1;
        while (true) {
            int mid = (lo + hi) / 2;
            if (m * mid + c < at(node, mid)) { swap(m, slope[node]); swap(c, icpt[node]); }  // the node keeps the winner at mid
            if (lo == hi) return;
            if (m * lo + c < at(node, lo)) { node = 2 * node; hi = mid; }
            else if (m * hi + c < at(node, hi)) { node = 2 * node + 1; lo = mid + 1; }
            else return;
        }
    }
    long long query(long long x) const {  // the lowest line on the path from the root to the leaf x
        int node = 1, lo = 0, hi = size - 1;
        long long best = INF;
        while (true) {
            best = min(best, at(node, x));
            if (lo == hi) return best;
            int mid = (lo + hi) / 2;
            if (x <= mid) { node = 2 * node; hi = mid; }
            else { node = 2 * node + 1; lo = mid + 1; }
        }
    }
};
// snippet:end

int main() {
    {
        LiChao tree(8);
        tree.add(2, 0);
        tree.add(-1, 10);
        cout << "x=3: " << tree.query(3) << "\n";
        cout << "x=5: " << tree.query(5) << "\n";
    }
    {
        LiChao tree(8);
        tree.add(1, 0);
        tree.add(1, -2);
        cout << "x=4: " << tree.query(4) << "\n";
    }
    // Check (not printed): 3000 random sets of up to 8 lines on the points 0..15, every point, against the minimum over all lines.
    mt19937 rng(9);
    for (int it = 0; it < 3000; it++) {
        LiChao tree(16);
        vector<pair<long long, long long>> lines;
        int cnt = rng() % 8 + 1;
        for (int t = 0; t < cnt; t++) {
            long long m = (long long)(rng() % 15) - 7, c = (long long)(rng() % 61) - 30;
            tree.add(m, c);
            lines.push_back({m, c});
            for (int x = 0; x < 16; x++) {
                long long best = INF;
                for (auto [mm, cc] : lines) best = min(best, mm * x + cc);
                if (tree.query(x) != best) return 1;
            }
        }
    }
}
