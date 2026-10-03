/*
Problem: AtCoder ABC 300 C Cross. A grid of '#' and '.' consists of non-touching diagonal crosses;
count the crosses of each size 1..min(H, W).
Input: H W (3 <= H, W <= 100), then H rows.
Output: S_1 .. S_N separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    // '#' at (r, c), treating cells outside the grid as '.'
    auto black = [&](int r, int c) {
        return r >= 0 && r < h && c >= 0 && c < w && g[r][c] == '#';
    };
    int n = min(h, w);
    vector<int> cnt(n + 1, 0);
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (!black(r, c)) continue;
            int size = 0;  // grow the cross while all four diagonal arms continue
            while (black(r + size + 1, c + size + 1) && black(r + size + 1, c - size - 1) &&
                   black(r - size - 1, c + size + 1) && black(r - size - 1, c - size - 1))
                size++;
            if (size >= 1) cnt[size]++;  // only a centre has all four diagonal neighbours black
        }
    for (int s = 1; s <= n; s++) cout << cnt[s] << (s < n ? ' ' : '\n');
}
