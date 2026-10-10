#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.1. Counting by the last step: the paths to a cell come from the cell above or the cell to the left, and the two
// groups do not overlap. A blocked cell keeps 0. Returns the whole table.
vector<vector<long long>> pathTable(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    vector<vector<long long>> cnt(h, vector<long long>(w, 0));
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') continue;
            if (r == 0 && c == 0) cnt[r][c] = 1;
            else cnt[r][c] = (r > 0 ? cnt[r - 1][c] : 0) + (c > 0 ? cnt[r][c - 1] : 0);
        }
    return cnt;
}
// snippet:end

long long brute(const vector<string>& g, int r, int c) {
    if (r < 0 || c < 0 || g[r][c] == '#') return 0;
    if (r == 0 && c == 0) return 1;
    return brute(g, r - 1, c) + brute(g, r, c - 1);
}
int main() {
    vector<string> g = {"....", ".#..", "...."};
    auto t = pathTable(g);
    for (auto& row : t) {
        for (size_t c = 0; c < row.size(); c++) cout << row[c] << (c + 1 < row.size() ? ' ' : '\n');
    }
    cout << "paths to the lower-right cell: " << t[2][3] << '\n';
    mt19937 rng(41);
    for (int round = 0; round < 300; round++) {
        int h = 1 + rng() % 5, w = 1 + rng() % 5;
        vector<string> b(h, string(w, '.'));
        for (auto& row : b) for (char& ch : row) if (rng() % 4 == 0) ch = '#';
        b[0][0] = '.';
        if (pathTable(b)[h - 1][w - 1] != brute(b, h - 1, w - 1)) return 1;
    }
}
