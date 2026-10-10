/*
Problem: CSES 1193, Labyrinth.
Input: n m, then n lines of m characters: '.' floor, '#' wall, 'A' start, 'B' end (exactly one of each).
Output: "YES" and the length of a shortest path from A to B with its moves (L, R, U, D), or "NO".
(This program checks the path it finds by walking it, and prints "YES" and the length only.)
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 2. A shortest route from 'A' to 'B' as a string of moves U, D, L, R; returns false if there is no route.
bool shortestMoves(const vector<string>& grid, string& moves) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    const char name[4] = {'U', 'D', 'L', 'R'};
    vector<vector<int>> cameBy(rows, vector<int>(cols, -1));  // the move that entered the cell; 4 marks the start
    int ar = 0, ac = 0, br = 0, bc = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'A') ar = r, ac = c;
            if (grid[r][c] == 'B') br = r, bc = c;
        }
    queue<pair<int, int>> q;
    cameBy[ar][ac] = 4;
    q.push({ar, ac});
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#' || cameBy[nr][nc] != -1) continue;
            cameBy[nr][nc] = d;
            q.push({nr, nc});
        }
    }
    if (cameBy[br][bc] == -1) return false;
    moves.clear();
    for (int r = br, c = bc; cameBy[r][c] != 4;) {  // walk back from B to A, undoing each move
        int d = cameBy[r][c];
        moves += name[d];
        r -= dr[d];
        c -= dc[d];
    }
    reverse(moves.begin(), moves.end());
    return true;
}
// snippet:end

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    string moves;
    if (!shortestMoves(grid, moves)) {
        cout << "NO\n";
        return 0;
    }
    // Check the answer: walk the moves from A over floor cells and end on B.
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
    if (grid[r][c] != 'B') return 2;
    cout << "YES\n" << moves.size() << "\n";
}
