/*
Problem: rooms of a map.
Input: R C, then R lines of C characters: '.' is floor, '#' is a wall.
Output: the number of rooms (floor cells joined through side neighbours), then the size of the largest room (0 if none).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 4.1.2 and 4.1.5. The size of every room, in the order the rooms are found (rows top to bottom, left to right).
vector<int> roomSizes(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<vector<bool>> seen(rows, vector<bool>(cols, false));
    vector<int> sizes;
    for (int r0 = 0; r0 < rows; r0++) {
        for (int c0 = 0; c0 < cols; c0++) {
            if (grid[r0][c0] == '#' || seen[r0][c0]) continue;
            int size = 0;
            queue<pair<int, int>> q;
            q.push({r0, c0});
            seen[r0][c0] = true;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                size++;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                    if (grid[nr][nc] == '#' || seen[nr][nc]) continue;
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
            sizes.push_back(size);
        }
    }
    return sizes;
}
// snippet:end

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    vector<int> sizes = roomSizes(grid);
    cout << sizes.size() << " " << (sizes.empty() ? 0 : *max_element(sizes.begin(), sizes.end())) << "\n";
}
