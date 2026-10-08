/*
Problem: count the paths from the top-left to the bottom-right cell of a grid that move only
right or down and never enter a blocked cell, modulo 10^9 + 7.
Input: H W (1 <= H, W <= 3000), then H lines of W characters, '.' free and '#' blocked.
Output: the number of paths modulo 10^9 + 7 (0 if the start or the end is blocked).
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    // ways[c] = paths to cell (r, c) of the current row; the old value is the cell above (Theorem 3.5.1)
    vector<long long> ways(w, 0);
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') {
                ways[c] = 0;                              // no path ends on a blocked cell
            } else if (r == 0 && c == 0) {
                ways[c] = 1;                              // the empty path
            } else if (c > 0) {
                ways[c] = (ways[c] + ways[c - 1]) % MOD;  // from above + from the left
            }                                             // c == 0: only from above, unchanged
        }
    }
    cout << ways[w - 1] << "\n";
}
