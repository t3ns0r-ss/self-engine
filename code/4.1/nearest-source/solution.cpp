/*
Problem: distance to the nearest source on a map.
Input: R C, then R lines of C characters: '.' is floor, '#' is a wall, 'S' is a source (also a floor cell).
Output: three numbers: the sum of the distances of the floor cells that can be reached, the largest of those distances,
and the number of floor cells that cannot be reached from any source. The distance counts side-neighbour steps.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.4. For every cell, the fewest steps to the nearest 'S' cell (-1 for walls and cells no source reaches).
vector<vector<int>> nearestSource(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 'S') {  // every source starts at distance 0
                dist[r][c] = 0;
                q.push({r, c});
            }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}
// snippet:end

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    auto dist = nearestSource(grid);
    long long sum = 0;
    int largest = 0, unreachable = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '#') continue;
            if (dist[r][c] == -1) unreachable++;
            else {
                sum += dist[r][c];
                largest = max(largest, dist[r][c]);
            }
        }
    cout << sum << " " << largest << " " << unreachable << "\n";
}
