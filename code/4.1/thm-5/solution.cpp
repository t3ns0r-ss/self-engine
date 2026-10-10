#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.5. The fewest steps from cell (sr, sc) to every cell of a grid ('#' is a wall, '.' is free), moving up, down, left or
// right; -1 marks a cell that cannot be reached.
vector<vector<int>> gridBfs(const vector<string>& grid, int sr, int sc) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;  // outside the grid
            if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;     // wall, or seen before
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}
// snippet:end

void printRun(const vector<string>& grid, int sr, int sc) {
    auto dist = gridBfs(grid, sr, sc);
    for (size_t r = 0; r < grid.size(); r++) {
        for (size_t c = 0; c < grid[r].size(); c++) {
            if (c) cout << ' ';
            if (grid[r][c] == '#') cout << '#';
            else cout << dist[r][c];
        }
        cout << "\n";
    }
}

int main() {
    cout << "grid \"....\" \".##.\" \"....\", start (0, 0):\n";
    printRun({"....", ".##.", "...."}, 0, 0);
    cout << "grid \".#.\" \".#.\", start (0, 0):\n";
    printRun({".#.", ".#."}, 0, 0);
    cout << "grid \"..\" \"..\", start (1, 1):\n";
    printRun({"..", ".."}, 1, 1);
    // Check against repeated relaxation on every 3 x 4 grid (2^12 wall patterns) and every free start cell.
    int rows = 3, cols = 4;
    for (int mask = 0; mask < (1 << (rows * cols)); mask++) {
        vector<string> grid(rows, string(cols, '.'));
        for (int i = 0; i < rows * cols; i++)
            if (mask >> i & 1) grid[i / cols][i % cols] = '#';
        for (int sr = 0; sr < rows; sr++)
            for (int sc = 0; sc < cols; sc++) {
                if (grid[sr][sc] == '#') continue;
                const int INF = 1e9;
                vector<vector<int>> best(rows, vector<int>(cols, INF));
                best[sr][sc] = 0;
                for (int round = 0; round < rows * cols; round++)
                    for (int r = 0; r < rows; r++)
                        for (int c = 0; c < cols; c++) {
                            if (grid[r][c] == '#') continue;
                            if (r > 0 && grid[r - 1][c] != '#') best[r][c] = min(best[r][c], best[r - 1][c] + 1);
                            if (r + 1 < rows && grid[r + 1][c] != '#') best[r][c] = min(best[r][c], best[r + 1][c] + 1);
                            if (c > 0 && grid[r][c - 1] != '#') best[r][c] = min(best[r][c], best[r][c - 1] + 1);
                            if (c + 1 < cols && grid[r][c + 1] != '#') best[r][c] = min(best[r][c], best[r][c + 1] + 1);
                        }
                auto dist = gridBfs(grid, sr, sc);
                for (int r = 0; r < rows; r++)
                    for (int c = 0; c < cols; c++)
                        if (grid[r][c] != '#' && dist[r][c] != (best[r][c] >= INF ? -1 : best[r][c])) return 1;
            }
    }
}
