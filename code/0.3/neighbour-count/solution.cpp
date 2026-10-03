/*
Problem: in an H x W grid of '#' (mine) and '.', replace every '.' by the number of mines
among its 8 neighbours.
Input: H W, then H lines of W characters.
Output: the H lines of the new grid.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    vector<string> out = g;
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') continue;
            int mines = 0;
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;  // the cell itself is not a neighbour
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < h && nc >= 0 && nc < w && g[nr][nc] == '#') mines++;
                }
            out[r][c] = char('0' + mines);
        }
    for (auto& row : out) cout << row << "\n";
}
