#include <bits/stdc++.h>
using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// Method for rooms: one traversal per unvisited floor cell, counting the traversals.
int countRooms(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size(), rooms = 0;
    vector<vector<bool>> seen(rows, vector<bool>(cols, false));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '#' || seen[r][c]) continue;
            rooms++;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = true;
            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = cr + dr[d], nc = cc + dc[d];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                    if (grid[nr][nc] == '#' || seen[nr][nc]) continue;
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    return rooms;
}

// Brute force for rooms: two floor cells are in one room if repeated merging of side-adjacent floor cells joins them.
int countRoomsBrute(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    vector<int> label(rows * cols);
    iota(label.begin(), label.end(), 0);
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '#') continue;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
                    int a = label[r * cols + c], b = label[nr * cols + nc];
                    if (a != b) {
                        int low = min(a, b);
                        label[r * cols + c] = label[nr * cols + nc] = low;
                        changed = true;
                    }
                }
            }
    }
    set<int> distinct;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] != '#') distinct.insert(label[r * cols + c]);
    return distinct.size();
}

// Method for the door puzzle: search over cells only, treating the door D as an ordinary floor cell (the key K is ignored).
int cellOnlySteps(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size(), sr = 0, sc = 0, tr = 0, tc = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') sr = r, sc = c;
            if (grid[r][c] == 'T') tr = r, tc = c;
        }
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
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
    return dist[tr][tc];
}

// Brute force for the door puzzle: try every sequence of at most `depth` moves, with the key picked up on entering K and the door
// D passable only with the key; increase the depth until the target T is reached.
bool tryMoves(const vector<string>& grid, int r, int c, bool key, int left) {
    if (grid[r][c] == 'T') return true;
    if (left == 0) return false;
    int rows = grid.size(), cols = grid[0].size();
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
        if (grid[nr][nc] == 'D' && !key) continue;
        if (tryMoves(grid, nr, nc, key || grid[nr][nc] == 'K', left - 1)) return true;
    }
    return false;
}
int doorSteps(const vector<string>& grid) {
    int sr = 0, sc = 0;
    for (size_t r = 0; r < grid.size(); r++)
        for (size_t c = 0; c < grid[r].size(); c++)
            if (grid[r][c] == 'S') sr = r, sc = c;
    for (int depth = 0; depth <= 12; depth++)
        if (tryMoves(grid, sr, sc, false, depth)) return depth;
    return -1;
}

int main() {
    // P1: rooms of a 3 x 5 map ('#' wall, '.' floor).
    vector<string> map = {"..#..", ".##..", "#..#."};
    cout << "P1 brute=" << countRoomsBrute(map) << " method=" << countRooms(map) << "\n";
    // N1: S to T with a door D that opens only after the key K has been picked up.
    vector<string> doors = {"S.D.T", "#K###"};
    cout << "N1 brute=" << doorSteps(doors) << " method=" << cellOnlySteps(doors) << "\n";
}
