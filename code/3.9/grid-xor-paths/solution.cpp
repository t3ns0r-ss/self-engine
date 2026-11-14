/*
Problem: an n x m grid of numbers. A path goes from the top-left cell to the bottom-right cell, moving only right or down.
Count the paths whose cells have exclusive or (xor) equal to k.
Input: n m k, then n rows of m numbers (1 <= n, m <= 20, 0 <= a_ij, k < 2^60).
Output: the number of such paths.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.9.1 applied to a path: cut it after half = (n + m - 2) / 2 steps. Every path crosses the diagonal i + j = half in exactly one cell.
long long countXorPaths(const vector<vector<long long>>& a, long long k) {
    int n = a.size(), m = a[0].size(), half = (n + m - 2) / 2;
    vector<map<long long, long long>> forward(n);  // forward[i]: xor of the cells from the start up to and including (i, half - i), with the number of ways
    function<void(int, int, long long)> goForward = [&](int i, int j, long long x) {
        x ^= a[i][j];
        if (i + j == half) { forward[i][x]++; return; }
        if (i + 1 < n) goForward(i + 1, j, x);
        if (j + 1 < m) goForward(i, j + 1, x);
    };
    goForward(0, 0, 0);
    long long count = 0;
    function<void(int, int, long long)> goBack = [&](int i, int j, long long x) {
        if (i + j == half) {  // the meeting cell is already in the forward xor, so it is not added again
            auto it = forward[i].find(x ^ k);
            if (it != forward[i].end()) count += it->second;
            return;
        }
        x ^= a[i][j];
        if (i > 0) goBack(i - 1, j, x);
        if (j > 0) goBack(i, j - 1, x);
    };
    goBack(n - 1, m - 1, 0);
    return count;
}
// snippet:end

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<vector<long long>> a(n, vector<long long>(m));
    for (auto& row : a) for (auto& x : row) cin >> x;
    cout << countXorPaths(a, k) << "\n";
}
