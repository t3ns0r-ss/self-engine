#include <bits/stdc++.h>
using namespace std;

// Brute force: relax every cell from its neighbours until nothing changes (no queue).
int main() {
    int H, W;
    cin >> H >> W;
    vector<string> g(H);
    for (auto& row : g) cin >> row;
    const int INF = 1e9;
    vector<vector<int>> d(H, vector<int>(W, INF));
    int gr = 0, gc = 0;
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++) {
            if (g[r][c] == 'S') d[r][c] = 0;
            if (g[r][c] == 'G') { gr = r; gc = c; }
        }
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < H; r++)
            for (int c = 0; c < W; c++) {
                if (g[r][c] == '#') continue;
                const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= H || nc < 0 || nc >= W || d[nr][nc] == INF) continue;
                    if (d[nr][nc] + 1 < d[r][c]) { d[r][c] = d[nr][nc] + 1; changed = true; }
                }
            }
    }
    cout << (d[gr][gc] == INF ? -1 : d[gr][gc]) << "\n";
}
