/*
Problem: AtCoder ABC 378 D, Count Simple Paths. Count the walks of K moves on an H x W grid that start
on an empty cell, move to side-adjacent empty cells, and never visit a cell twice.
Input: H W K (H, W <= 10, K <= 11), then H rows of '.' (empty) and '#' (blocked).
Output: the number of such walks.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// ABC 378 D. Count the walks of K moves that start on an empty cell and never visit a cell twice: backtracking where the
// check reads only cells already on the walk, with the visited mark undone after each call.
long long countWalks(const vector<string>& grid, int K) {
    int H = grid.size(), W = grid[0].size();
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    function<long long(int, int, int)> rec = [&](int r, int c, int movesLeft) -> long long {
        if (movesLeft == 0) return 1;  // a complete walk
        long long ways = 0;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W || grid[nr][nc] == '#' || visited[nr][nc]) continue;
            visited[nr][nc] = true;
            ways += rec(nr, nc, movesLeft - 1);
            visited[nr][nc] = false;  // undo
        }
        return ways;
    };
    long long total = 0;
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++) {
            if (grid[r][c] == '#') continue;
            visited[r][c] = true;
            total += rec(r, c, K);
            visited[r][c] = false;
        }
    return total;
}
// snippet:end

int main() {
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> grid(H);
    for (auto& row : grid) cin >> row;
    cout << countWalks(grid, K) << "\n";
}
