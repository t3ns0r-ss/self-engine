/*
Problem: CSES 1638, Grid Paths I. Count the paths from the upper-left to the lower-right square of an n x n grid
that move only right or down and never enter a trap, modulo 10^9 + 7.
Input: n (n <= 1000), then n lines of n characters, '.' empty and '*' a trap.
Output: the number of paths modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1638. The paths from the upper-left to the lower-right square moving right or down, never entering a trap.
long long trapPaths(const vector<string>& g) {
    const long long MOD = 1'000'000'007;
    int n = g.size();
    vector<vector<long long>> ways(n + 1, vector<long long>(n + 1, 0));  // a border of zeros outside the grid
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++) {
            if (g[r - 1][c - 1] == '*') continue;  // a trap keeps 0
            if (r == 1 && c == 1) ways[r][c] = 1;
            else ways[r][c] = (ways[r - 1][c] + ways[r][c - 1]) % MOD;  // from above + from the left
        }
    return ways[n][n];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto& row : g) cin >> row;
    cout << trapPaths(g) << "\n";
}
