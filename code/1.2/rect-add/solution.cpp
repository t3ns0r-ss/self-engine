/*
Problem: an R x C grid of zeros; q updates "x1 y1 x2 y2 v" add v to every cell of the rectangle
(1-based rows x1..x2, columns y1..y2). Print the final grid.
Input: R C q (R*C <= 10^6, q <= 2*10^5), then the updates (|v| <= 10^9).
Output: R lines of C values.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.4, part 3. Add v to every cell of a rectangle (1-based corners) for each update: four corner changes,
// then 2D prefix sums give the grid.
vector<vector<long long>> rectAdd(int R, int C, const vector<array<long long, 5>>& updates) {
    vector<vector<long long>> d(R + 2, vector<long long>(C + 2, 0));  // one extra row and column for corners past the edge
    for (auto [x1, y1, x2, y2, v] : updates) {
        d[x1][y1] += v;
        d[x1][y2 + 1] -= v;
        d[x2 + 1][y1] -= v;
        d[x2 + 1][y2 + 1] += v;
    }
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) d[x][y] += d[x - 1][y] + d[x][y - 1] - d[x - 1][y - 1];
    return d;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, q;
    cin >> R >> C >> q;
    vector<array<long long, 5>> updates(q);
    for (auto& u : updates) cin >> u[0] >> u[1] >> u[2] >> u[3] >> u[4];
    vector<vector<long long>> g = rectAdd(R, C, updates);
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) cout << g[x][y] << (y < C ? ' ' : '\n');
}
