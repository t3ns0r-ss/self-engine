#include <bits/stdc++.h>
using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// Method: 0-1 BFS (Theorem 4.3.2) on a grid where stepping onto '.' costs 0 and onto '#' costs 1 (a wall broken);
// at most `limit` walls may be broken when limit >= 0, otherwise any number. Returns -1 when the target cannot be reached.
int zeroOne(const vector<string>& grid, int limit) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    deque<pair<int, int>> line;
    dist[0][0] = 0;
    line.push_back({0, 0});
    while (!line.empty()) {
        auto [r, c] = line.front();
        line.pop_front();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int w = grid[nr][nc] == '#' ? 1 : 0;
            if (dist[r][c] + w < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + w;
                if (w == 0) line.push_front({nr, nc});
                else line.push_back({nr, nc});
            }
        }
    }
    int best = dist[rows - 1][cols - 1];
    if (best == INT_MAX) return -1;
    if (limit >= 0 && best > limit) return -1;
    return best;
}

// Brute force for the number of walls: Floyd-Warshall on the cells with the cost of entering a cell.
int floydCells(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size(), n = rows * cols;
    const int INF = 1e9;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                d[r * cols + c][nr * cols + nc] = grid[nr][nc] == '#' ? 1 : 0;
            }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    return d[0][n - 1] >= INF ? -1 : d[0][n - 1];
}

// Brute force for "at most `limit` walls": try every set of at most `limit` walls to remove, then count steps... here the cost
// is the number of walls, so check by searching over (cell, walls used so far).
int searchWithLimit(const vector<string>& grid, int limit) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<vector<bool>>> seen(rows, vector<vector<bool>>(cols, vector<bool>(limit + 2, false)));
    queue<array<int, 3>> q;
    seen[0][0][0] = true;
    q.push({0, 0, 0});
    int best = -1;
    while (!q.empty()) {
        auto [r, c, used] = q.front();
        q.pop();
        if (r == rows - 1 && c == cols - 1) {
            best = best == -1 ? used : min(best, used);
            continue;
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int nu = used + (grid[nr][nc] == '#');
            if (nu > limit || seen[nr][nc][nu]) continue;
            seen[nr][nc][nu] = true;
            q.push({nr, nc, nu});
        }
    }
    return best;
}

int main() {
    // P1: fewest walls to break from the top-left to the bottom-right corner of a 3 x 4 map (all walls on the way cost 1).
    vector<string> map = {".#..", "##.#", "...."};
    cout << "P1 brute=" << floydCells(map) << " method=" << zeroOne(map, -1) << "\n";
    // N1: the row ".#.#." with at most ONE wall allowed to break; the method above breaks as many as it likes.
    vector<string> row = {".#.#."};
    cout << "N1 brute=" << (searchWithLimit(row, 1) == -1 ? string("impossible") : to_string(searchWithLimit(row, 1))) << " method=" << zeroOne(row, -2) << "\n";
}
