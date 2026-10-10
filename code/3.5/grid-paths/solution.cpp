/*
Problem: count the paths from the top-left to the bottom-right cell of a grid that move only
right or down and never enter a blocked cell, modulo 10^9 + 7.
Input: H W (1 <= H, W <= 3000), then H lines of W characters, '.' free and '#' blocked.
Output: the number of paths modulo 10^9 + 7 (0 if the start or the end is blocked).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.1. ways[c] = the paths to cell (r, c) of the current row; the old value is the cell above, ways[c - 1] the
// cell to the left. A blocked cell keeps no path.
long long gridPaths(const vector<string>& g) {
    const long long MOD = 1'000'000'007;
    int h = g.size(), w = g[0].size();
    vector<long long> ways(w, 0);
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') ways[c] = 0;
            else if (r == 0 && c == 0) ways[c] = 1;  // the empty path
            else if (c > 0) ways[c] = (ways[c] + ways[c - 1]) % MOD;  // from above + from the left
        }
    return ways[w - 1];
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    cout << gridPaths(g) << "\n";
}
