#include <bits/stdc++.h>
using namespace std;

// Repeat "improve every cell from its four neighbours" until nothing changes.
int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    vector<vector<int>> d(h, vector<int>(w, 1000000));
    d[0][0] = 0;
    for (bool changed = true; changed;) {
        changed = false;
        for (int x = 0; x < h; x++)
            for (int y = 0; y < w; y++) {
                int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
                    int c = d[x][y] + (g[nx][ny] == '#');
                    if (c < d[nx][ny]) d[nx][ny] = c, changed = true;
                }
            }
    }
    cout << d[h - 1][w - 1] << "\n";
}
