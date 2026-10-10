/*
Problem: AtCoder ABC 176 D, Wizard in Maze.
Input: H W, the start "Ch Cw", the target "Dh Dw", then H lines of W characters ('.' road, '#' wall).
He walks to an adjacent road square for free, or uses magic to warp to any road square in the 5 x 5 area around him.
Output: the fewest uses of magic to reach the target, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 2. 0-1 BFS: walking costs 0 (front of the deque), a warp costs 1 (back of the deque).
int fewestMagic(const vector<string>& g, int sx, int sy, int tx, int ty) {
    int h = g.size(), w = g[0].size();
    vector<vector<int>> dist(h, vector<int>(w, INT_MAX));
    deque<pair<int, int>> dq;
    dist[sx][sy] = 0;
    dq.push_back({sx, sy});
    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();
        for (int dx = -2; dx <= 2; dx++)
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || ny < 0 || nx >= h || ny >= w || g[nx][ny] == '#') continue;
                bool walk = abs(dx) + abs(dy) == 1;
                int cost = walk ? 0 : 1;
                if (dist[x][y] + cost < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + cost;
                    if (cost) dq.push_back({nx, ny});
                    else dq.push_front({nx, ny});
                }
            }
    }
    return dist[tx][ty] == INT_MAX ? -1 : dist[tx][ty];
}
// snippet:end

int main() {
    int h, w, sx, sy, tx, ty;
    cin >> h >> w >> sx >> sy >> tx >> ty;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    cout << fewestMagic(g, sx - 1, sy - 1, tx - 1, ty - 1) << "\n";
}
