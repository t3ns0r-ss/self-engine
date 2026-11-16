/*
Drill (about 5 minutes). A grid of H rows and W columns: '.' is free, '#' is a wall, 'S' the start, 'G' the goal.
One step moves to a free neighbour (up, down, left or right). Print the fewest steps from S to G, or -1.
Input: H W, then H lines of W characters. H, W <= 1000. S and G occur once.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Grid BFS skeleton: a distance array filled with -1 doubles as the visited mark; a direction table avoids four copies.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    cin >> H >> W;
    vector<string> g(H);
    for (auto& row : g) cin >> row;
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> q;
    int gr = -1, gc = -1;
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++) {
            if (g[r][c] == 'S') { dist[r][c] = 0; q.push({r, c}); }
            if (g[r][c] == 'G') { gr = r; gc = c; }
        }
    const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;  // stay inside the grid
            if (g[nr][nc] == '#' || dist[nr][nc] != -1) continue;   // wall or already reached
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    cout << dist[gr][gc] << "\n";
}
// snippet:end
