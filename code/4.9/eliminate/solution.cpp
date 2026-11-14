/*
Problem: walking through walls.
Input: R C k, then R lines of C characters: '.' open cell, '#' obstacle. The top-left and bottom-right cells are '.'.
A step goes to a side neighbour. You may step onto at most k obstacles during the whole walk.
Output: the fewest steps from the top-left to the bottom-right cell, or -1 if it cannot be done.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.9.4. Fewest steps from the top-left to the bottom-right cell when at most k obstacles may be entered. A state is (cell,
// obstacles still allowed); it is entered only if it has more left than every earlier visit of the same cell.
int fewestSteps(const vector<string>& grid, int k) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<int> bestLeft(rows * cols, -1);  // most obstacles still allowed on any visit so far
    queue<array<int, 4>> q;                 // row, column, obstacles left, steps
    bestLeft[0] = k;
    q.push({0, 0, k, 0});
    while (!q.empty()) {
        auto [r, c, left, steps] = q.front();
        q.pop();
        if (r == rows - 1 && c == cols - 1) return steps;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int nextLeft = left - (grid[nr][nc] == '#');
            if (nextLeft < 0 || nextLeft <= bestLeft[nr * cols + nc]) continue;  // too many obstacles, or dominated
            bestLeft[nr * cols + nc] = nextLeft;
            q.push({nr, nc, nextLeft, steps + 1});
        }
    }
    return -1;
}
// snippet:end

int main() {
    int rows, cols, k;
    cin >> rows >> cols >> k;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    cout << fewestSteps(grid, k) << "\n";
}
