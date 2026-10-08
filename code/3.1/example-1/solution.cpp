/*
Problem: AtCoder ABC 378 D, Count Simple Paths. Count the walks of K moves on an H x W grid that start
on an empty cell, move to side-adjacent empty cells, and never visit a cell twice.
Input: H W K (H, W <= 10, K <= 11), then H rows of '.' (empty) and '#' (blocked).
Output: the number of such walks.
*/
#include <bits/stdc++.h>
using namespace std;

int H, W, K;
vector<string> grid;
vector<vector<bool>> visited;
const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

long long rec(int r, int c, int movesLeft) {
    if (movesLeft == 0) return 1;  // a complete walk
    long long ways = 0;
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        // the check reads only cells already on the walk (Theorem 3.1.1)
        if (nr < 0 || nr >= H || nc < 0 || nc >= W || grid[nr][nc] == '#' || visited[nr][nc]) continue;
        visited[nr][nc] = true;
        ways += rec(nr, nc, movesLeft - 1);
        visited[nr][nc] = false;  // undo
    }
    return ways;
}

int main() {
    cin >> H >> W >> K;
    grid.resize(H);
    for (auto& row : grid) cin >> row;
    visited.assign(H, vector<bool>(W, false));
    long long total = 0;
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++) {
            if (grid[r][c] == '#') continue;
            visited[r][c] = true;
            total += rec(r, c, K);
            visited[r][c] = false;
        }
    cout << total << "\n";
}
