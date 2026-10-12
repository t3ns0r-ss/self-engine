#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, c;
    cin >> r >> c;
    vector<vector<int>> grid(r, vector<int>(c));
    for (auto& row : grid)
        for (int& x : row) cin >> x;
    int best = 1;
    function<int(int, int)> go = [&](int i, int j) {
        int len = 1;
        const int di[] = {1, -1, 0, 0}, dj[] = {0, 0, 1, -1};
        for (int d = 0; d < 4; d++) {
            int x = i + di[d], y = j + dj[d];
            if (x >= 0 && x < r && y >= 0 && y < c && grid[x][y] > grid[i][j]) len = max(len, 1 + go(x, y));
        }
        return len;
    };
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) best = max(best, go(i, j));
    cout << best << "\n";
}
