#include <bits/stdc++.h>
using namespace std;

// Repeated relaxation of the distance from A over all floor cells until nothing changes.
int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    const int INF = 1e9;
    vector<vector<int>> dist(rows, vector<int>(cols, INF));
    int br = 0, bc = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'A') dist[r][c] = 0;
            if (grid[r][c] == 'B') br = r, bc = c;
        }
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '#') continue;
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++) {
                        if (abs(dr) + abs(dc) != 1) continue;
                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
                        if (dist[nr][nc] + 1 < dist[r][c]) {
                            dist[r][c] = dist[nr][nc] + 1;
                            changed = true;
                        }
                    }
            }
    }
    if (dist[br][bc] >= INF) cout << "NO\n";
    else cout << "YES\n" << dist[br][bc] << "\n";
}
