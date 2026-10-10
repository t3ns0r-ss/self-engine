#include <bits/stdc++.h>
using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// Distances on a grid from a set of starting cells (all at distance 0); -1 for cells that are walls or unreachable.
vector<vector<int>> gridDist(const vector<string>& grid, const vector<pair<int, int>>& starts) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    for (auto [r, c] : starts) {
        dist[r][c] = 0;
        q.push({r, c});
    }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}

int main() {
    // P1: the time at which everything reachable has been reached when fire starts at every S and spreads one cell per minute.
    vector<string> grid = {"S...#", ".##..", "...#.", "#.S.."};
    vector<pair<int, int>> sources;
    for (size_t r = 0; r < grid.size(); r++)
        for (size_t c = 0; c < grid[r].size(); c++)
            if (grid[r][c] == 'S') sources.push_back({r, c});
    // Brute force: one search per source, keep the smallest distance of each cell.
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> best(rows, vector<int>(cols, -1));
    for (auto s : sources) {
        auto d = gridDist(grid, {s});
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (d[r][c] != -1 && (best[r][c] == -1 || d[r][c] < best[r][c])) best[r][c] = d[r][c];
    }
    int bruteMax = 0, methodMax = 0;
    auto together = gridDist(grid, sources);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            bruteMax = max(bruteMax, best[r][c]);
            methodMax = max(methodMax, together[r][c]);
        }
    cout << "P1 brute=" << bruteMax << " method=" << methodMax << "\n";
    // N1: path 1-2-3-4-5; the source 1 starts at minute 0, the source 5 starts at minute 3. The earliest minute at which vertex 4
    // is reached is the smallest (start minute + distance) over the sources; the method above lets both sources start at minute 0.
    int startMinute[2] = {0, 3};
    int source[2] = {1, 5};
    int target = 4;
    int brute = INT_MAX;
    for (int i = 0; i < 2; i++) brute = min(brute, startMinute[i] + abs(source[i] - target));
    int method = INT_MAX;
    for (int i = 0; i < 2; i++) method = min(method, abs(source[i] - target));
    cout << "N1 brute=" << brute << " method=" << method << "\n";
}
