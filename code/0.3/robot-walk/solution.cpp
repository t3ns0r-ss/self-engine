/*
Problem: a robot on an H x W grid of '.' (free) and '#' (wall) starts at (r, c), a free cell,
facing up. Commands: F moves one cell forward unless that cell is a wall or outside the grid
(then it stays), L and R turn 90 degrees left or right. Print the final cell.
Input: H W r c, then H lines of W characters, then the command string.
Output: the final row and column (0-based).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, r, c;
    cin >> h >> w >> r >> c;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    string cmd;
    cin >> cmd;

    const int dr[4] = {-1, 0, 1, 0};  // up, right, down, left: turning right is +1
    const int dc[4] = {0, 1, 0, -1};
    int d = 0;  // facing up
    for (char ch : cmd) {
        if (ch == 'R') d = (d + 1) % 4;
        else if (ch == 'L') d = (d + 3) % 4;  // +3 instead of -1 keeps d non-negative
        else {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < h && nc >= 0 && nc < w && g[nr][nc] != '#') {  // bounds first, then the wall
                r = nr;
                c = nc;
            }
        }
    }
    cout << r << " " << c << "\n";
}
