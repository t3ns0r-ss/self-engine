#include <bits/stdc++.h>
using namespace std;

/*
Problem: a set of lines y = m x + c, empty at first, and q operations. "1 m c" adds the line. "2 x" asks for the smallest value of
y at the integer point x among the lines added so far (0 <= x < 64); print INF if there is no line yet.
Input: q, then the q operations. Output: one line for each question.
*/

const long long INF = LLONG_MAX / 4;

// snippet:begin
// Theorem 7.3.6. A tree over the points 0..size-1. Each node keeps one line: the one that is lower at the middle of its range.
// The other line can be lower than it on one side only, so it is pushed down into that child alone.
struct LiChao {
    int size;
    vector<long long> slope, icpt;  // the line of each node; slope 0 and intercept INF means "no line"
    LiChao(int size) : size(size), slope(4 * size, 0), icpt(4 * size, INF) {}
    long long at(int node, long long x) const { return slope[node] * x + icpt[node]; }
    void add(long long m, long long c) {
        int node = 1, lo = 0, hi = size - 1;
        while (true) {
            int mid = (lo + hi) / 2;
            if (m * mid + c < at(node, mid)) { swap(m, slope[node]); swap(c, icpt[node]); }  // the node keeps the winner at mid
            if (lo == hi) return;
            if (m * lo + c < at(node, lo)) { node = 2 * node; hi = mid; }                   // the loser wins somewhere on the left
            else if (m * hi + c < at(node, hi)) { node = 2 * node + 1; lo = mid + 1; }      // ... or somewhere on the right
            else return;                                                                     // ... or nowhere
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
    int q;
    cin >> q;
    LiChao tree(64);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long m, c;
            cin >> m >> c;
            tree.add(m, c);
        } else {
            long long x;
            cin >> x;
            long long ans = tree.query(x);
            if (ans >= INF / 2) cout << "INF\n";
            else cout << ans << "\n";
        }
    }
}
