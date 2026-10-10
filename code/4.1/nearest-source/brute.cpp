#include <bits/stdc++.h>
using namespace std;

// Repeated relaxation: dist[cell] = min(dist[cell], dist[neighbour] + 1) over all cells, until nothing changes.
int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    const int INF = 1e9;
    vector<vector<int>> dist(rows, vector<int>(cols, INF));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'S') dist[r][c] = 0;
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
    long long sum = 0;
    int largest = 0, unreachable = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '#') continue;
            if (dist[r][c] >= INF) unreachable++;
            else {
                sum += dist[r][c];
                largest = max(largest, dist[r][c]);
            }
        }
    cout << sum << " " << largest << " " << unreachable << "\n";
}
