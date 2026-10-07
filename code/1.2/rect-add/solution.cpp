/*
Problem: an R x C grid of zeros; q updates "x1 y1 x2 y2 v" add v to every cell of the rectangle
(1-based rows x1..x2, columns y1..y2). Print the final grid.
Input: R C q (R*C <= 10^6, q <= 2*10^5), then the updates (|v| <= 10^9).
Output: R lines of C values.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, q;
    cin >> R >> C >> q;
    // 2D difference array with one extra row and column for the corners past the edge
    vector<vector<long long>> d(R + 2, vector<long long>(C + 2, 0));
    while (q--) {
        int x1, y1, x2, y2;
        long long v;
        cin >> x1 >> y1 >> x2 >> y2 >> v;
        d[x1][y1] += v;  // four corners (Theorem 1.2.4, part 3)
        d[x1][y2 + 1] -= v;
        d[x2 + 1][y1] -= v;
        d[x2 + 1][y2 + 1] += v;
    }
    // 2D prefix sums of d, computed in place, give the grid
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) {
            d[x][y] += d[x - 1][y] + d[x][y - 1] - d[x - 1][y - 1];
            cout << d[x][y] << (y < C ? ' ' : '\n');
        }
}
