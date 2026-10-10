/*
Problem: tunnelling through a maze.
Input: h w, then h lines of w characters: '.' is open ground and '#' is rock. Moves go one cell up, down, left or right.
Output: the fewest rock cells that must be dug through to get from the top-left cell to the bottom-right cell
(digging a cell costs 1 for entering it; the start cell is free).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.2. Fewest rock cells entered on a way from the top-left to the bottom-right cell of the grid.
int fewestRocks(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    vector<vector<int>> dist(h, vector<int>(w, INT_MAX));
    deque<pair<int, int>> dq;
    dist[0][0] = 0;
    dq.push_back({0, 0});
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
            int cost = g[nx][ny] == '#';
            if (dist[x][y] + cost < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + cost;
                if (cost) dq.push_back({nx, ny});  // cost 1: to the back
                else dq.push_front({nx, ny});      // cost 0: to the front
            }
        }
    }
    return dist[h - 1][w - 1];
}
// snippet:end

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    cout << fewestRocks(g) << "\n";
}
