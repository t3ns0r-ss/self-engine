#include <bits/stdc++.h>
using namespace std;

// Repeated relaxation over all (cell, keys) states: dist[next] = min(dist[next], dist[state] + 1) until nothing changes.
int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    const int INF = 1e9;
    vector<vector<array<int, 16>>> dist(rows, vector<array<int, 16>>(cols));
    for (auto& row : dist)
        for (auto& cell : row) cell.fill(INF);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'S') dist[r][c][0] = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                for (int keys = 0; keys < 16; keys++) {
                    if (dist[r][c][keys] >= INF) continue;
                    for (int dr = -1; dr <= 1; dr++)
                        for (int dc = -1; dc <= 1; dc++) {
                            if (abs(dr) + abs(dc) != 1) continue;
                            int nr = r + dr, nc = c + dc;
                            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
                            char ch = grid[nr][nc];
                            int nextKeys = keys;
                            if (ch >= 'a' && ch <= 'd') nextKeys |= 1 << (ch - 'a');
                            if (ch >= 'A' && ch <= 'D' && !((keys >> (ch - 'A')) & 1)) continue;
                            if (dist[r][c][keys] + 1 < dist[nr][nc][nextKeys]) {
                                dist[nr][nc][nextKeys] = dist[r][c][keys] + 1;
                                changed = true;
                            }
                        }
                }
    }
    int best = INF;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'T')
                for (int keys = 0; keys < 16; keys++) best = min(best, dist[r][c][keys]);
    cout << (best >= INF ? -1 : best) << "\n";
}
