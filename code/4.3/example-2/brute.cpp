#include <bits/stdc++.h>
using namespace std;

// Repeat "improve every road square from the squares around it" until nothing changes.
int main() {
    int h, w, sx, sy, tx, ty;
    cin >> h >> w >> sx >> sy >> tx >> ty;
    sx--, sy--, tx--, ty--;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    vector<vector<int>> d(h, vector<int>(w, 1000000));
    d[sx][sy] = 0;
    for (bool changed = true; changed;) {
        changed = false;
        for (int x = 0; x < h; x++)
            for (int y = 0; y < w; y++) {
                if (g[x][y] == '#') continue;
                for (int nx = max(0, x - 2); nx <= min(h - 1, x + 2); nx++)
                    for (int ny = max(0, y - 2); ny <= min(w - 1, y + 2); ny++) {
                        if (g[nx][ny] == '#') continue;
                        bool adjacent = abs(nx - x) + abs(ny - y) == 1;
                        int c = d[x][y] + (adjacent ? 0 : 1);
                        if (c < d[nx][ny]) d[nx][ny] = c, changed = true;
                    }
            }
    }
    cout << (d[tx][ty] == 1000000 ? -1 : d[tx][ty]) << "\n";
}
