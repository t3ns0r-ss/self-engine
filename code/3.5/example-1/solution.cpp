/*
Problem: CSES 1638, Grid Paths I. Count the paths from the upper-left to the lower-right square of an n x n grid
that move only right or down and never enter a trap, modulo 10^9 + 7.
Input: n (n <= 1000), then n lines of n characters, '.' empty and '*' a trap.
Output: the number of paths modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

int main() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto& row : g) cin >> row;
    // ways[r][c] with a border of zeros: row 0 and column 0 are outside the grid
    vector<vector<long long>> ways(n + 1, vector<long long>(n + 1, 0));
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (g[r - 1][c - 1] == '*') continue;                        // a trap keeps 0
            if (r == 1 && c == 1) ways[r][c] = 1;                        // the start
            else ways[r][c] = (ways[r - 1][c] + ways[r][c - 1]) % MOD;   // from above + from the left
        }
    }
    cout << ways[n][n] << "\n";
}
