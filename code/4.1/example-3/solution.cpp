/*
Problem: CSES 1194, Monsters.
Input: n m, then n lines of m characters: '.' floor, '#' wall, 'A' you, 'M' a monster. Each step, you and every monster
may move to a side neighbour. You must reach a boundary cell without ever sharing a cell with a monster, whatever the monsters do.
Output: "YES" and the length of a path (then the path), or "NO".
(This program checks the path it finds by walking it, and prints "YES" and the length only.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 3. A shortest safe route from 'A' to a boundary cell as a string of moves, or false if there is none.
// A cell is safe to enter at step t only if every monster needs more than t steps to reach it.
bool escapeRoute(const vector<string>& grid, string& moves) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    const char name[4] = {'U', 'D', 'L', 'R'};
    const int FAR = INT_MAX;  // "no monster ever gets here"
    vector<vector<int>> monster(rows, vector<int>(cols, FAR));
    queue<pair<int, int>> q;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'M') {  // all monsters start together: one walk for all of them
                monster[r][c] = 0;
                q.push({r, c});
            }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#' || monster[nr][nc] != FAR) continue;
            monster[nr][nc] = monster[r][c] + 1;
            q.push({nr, nc});
        }
    }
    vector<vector<int>> cameBy(rows, vector<int>(cols, -1)), me(rows, vector<int>(cols, -1));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'A') {
                me[r][c] = 0;
                cameBy[r][c] = 4;  // 4 marks the start
                q.push({r, c});
            }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {  // a boundary cell: rebuild the moves
            moves.clear();
            for (int x = r, y = c; cameBy[x][y] != 4;) {
                int d = cameBy[x][y];
                moves += name[d];
                x -= dr[d];
                y -= dc[d];
            }
            reverse(moves.begin(), moves.end());
            return true;
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#' || me[nr][nc] != -1) continue;
            if (me[r][c] + 1 >= monster[nr][nc]) continue;  // a monster can be there at the same time or earlier
            me[nr][nc] = me[r][c] + 1;
            cameBy[nr][nc] = d;
            q.push({nr, nc});
        }
    }
    return false;
}
// snippet:end

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    string moves;
    if (!escapeRoute(grid, moves)) {
        cout << "NO\n";
        return 0;
    }
    // Check the answer: walk the moves from A over floor cells and end on the boundary.
    int r = 0, c = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (grid[i][j] == 'A') r = i, c = j;
    for (char ch : moves) {
        if (ch == 'U') r--;
        if (ch == 'D') r++;
        if (ch == 'L') c--;
        if (ch == 'R') c++;
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '#') return 2;
    }
    if (!(r == 0 || r == rows - 1 || c == 0 || c == cols - 1)) return 2;
    cout << "YES\n" << moves.size() << "\n";
}
