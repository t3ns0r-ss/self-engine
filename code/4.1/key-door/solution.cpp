/*
Problem: doors and keys.
Input: R C, then R lines of C characters: '.' floor, '#' wall, 'S' start, 'T' target, 'a'..'d' keys, 'A'..'D' doors.
A key is picked up by stepping on it; the door of the same letter (A for a) can be entered once you hold that key.
Output: the fewest steps (to a side neighbour) from S to T, or -1 if T cannot be reached.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.6. Fewest steps from 'S' to 'T' when keys 'a'-'d' open the doors 'A'-'D'. The state is the cell together with
// the set of keys held (4 bits), so there are rows * cols * 16 states; -1 if 'T' cannot be reached.
int fewestStepsWithKeys(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<int> dist(rows * cols * 16, -1);  // index (r * cols + c) * 16 + keys
    queue<array<int, 3>> q;                  // row, column, keys
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'S') {
                dist[(r * cols + c) * 16] = 0;
                q.push({r, c, 0});
            }
    while (!q.empty()) {
        auto [r, c, keys] = q.front();
        q.pop();
        int here = dist[(r * cols + c) * 16 + keys];
        if (grid[r][c] == 'T') return here;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
            char ch = grid[nr][nc];
            int nextKeys = keys;
            if ('a' <= ch && ch <= 'd') nextKeys |= 1 << (ch - 'a');
            if ('A' <= ch && ch <= 'D' && !(keys >> (ch - 'A') & 1)) continue;  // door without its key
            int& slot = dist[(nr * cols + nc) * 16 + nextKeys];
            if (slot != -1) continue;
            slot = here + 1;
            q.push({nr, nc, nextKeys});
        }
    }
    return -1;
}
// snippet:end

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    cout << fewestStepsWithKeys(grid) << "\n";
}
