/*
Problem: a robot on an H x W grid of '.' (free) and '#' (wall) starts at (r, c), a free cell,
facing up. Commands: F moves one cell forward unless that cell is a wall or outside the grid
(then it stays), L and R turn 90 degrees left or right. Print the final cell.
Input: H W r c, then H lines of W characters, then the command string.
Output: the final row and column (0-based).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.2. The robot's final cell. Directions are arrays; turning right is +1, left is +3 (never negative);
// the bounds are checked before the wall is read.
pair<int, int> walk(const vector<string>& g, int r, int c, const string& cmd) {
    int h = g.size(), w = g[0].size();
    const int dr[4] = {-1, 0, 1, 0};  // up, right, down, left
    const int dc[4] = {0, 1, 0, -1};
    int d = 0;  // facing up
    for (char ch : cmd) {
        if (ch == 'R') d = (d + 1) % 4;
        else if (ch == 'L') d = (d + 3) % 4;
        else {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < h && nc >= 0 && nc < w && g[nr][nc] != '#') r = nr, c = nc;
        }
    }
    return {r, c};
}
// snippet:end

int main() {
    int h, w, r, c;
    cin >> h >> w >> r >> c;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    string cmd;
    cin >> cmd;
    pair<int, int> end = walk(g, r, c, cmd);
    cout << end.first << " " << end.second << "\n";
}
