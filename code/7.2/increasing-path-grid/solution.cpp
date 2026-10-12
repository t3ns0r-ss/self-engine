#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 329, Longest Increasing Path in a Matrix. A grid of r rows and c columns with a number in each cell (r, c up to 1000).
From a cell you may move to a neighbour above, below, left or right whose number is larger. Print the largest number of cells on a path.
Input: r, c, then the grid.
Output: the length.
*/


// snippet:begin
// Theorem 7.2.4 with the order made by sorting: a move always goes to a larger number, so the cells in increasing order of their numbers
// are a topological order (equal numbers have no edge between them). dp[cell] = 1 + the best neighbour with a smaller number.
int longestIncreasingPath(const vector<vector<int>>& grid) {
    int r = grid.size(), c = grid[0].size();
    vector<array<int, 2>> cells;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) cells.push_back({i, j});
    sort(cells.begin(), cells.end(), [&](const array<int, 2>& a, const array<int, 2>& b) { return grid[a[0]][a[1]] < grid[b[0]][b[1]]; });
    vector<vector<int>> dp(r, vector<int>(c, 1));
    int best = 1;
    for (auto [i, j] : cells) {
        const int di[] = {1, -1, 0, 0}, dj[] = {0, 0, 1, -1};
        for (int d = 0; d < 4; d++) {
            int x = i + di[d], y = j + dj[d];
            if (x >= 0 && x < r && y >= 0 && y < c && grid[x][y] < grid[i][j]) dp[i][j] = max(dp[i][j], dp[x][y] + 1);
        }
        best = max(best, dp[i][j]);
    }
    return best;
}
// snippet:end

int main() {
    int r, c;
    cin >> r >> c;
    vector<vector<int>> grid(r, vector<int>(c));
    for (auto& row : grid)
        for (int& x : row) cin >> x;
    cout << longestIncreasingPath(grid) << "\n";
}
