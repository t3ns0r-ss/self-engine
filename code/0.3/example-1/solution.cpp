/*
Problem: AtCoder ABC 300 C Cross. A grid of '#' and '.' consists of non-touching diagonal crosses;
count the crosses of each size 1..min(H, W).
Input: H W (3 <= H, W <= 100), then H rows.
Output: S_1 .. S_N separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// cnt[s] = number of crosses of size s. A cell is a centre of size s when its four diagonal arms
// reach s cells each; cells outside the grid count as '.'.
vector<int> countCrosses(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    auto black = [&](int r, int c) { return r >= 0 && r < h && c >= 0 && c < w && g[r][c] == '#'; };
    vector<int> cnt(min(h, w) + 1, 0);
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (!black(r, c)) continue;
            int size = 0;  // grow the cross while all four diagonal arms continue
            while (black(r + size + 1, c + size + 1) && black(r + size + 1, c - size - 1) &&
                   black(r - size - 1, c + size + 1) && black(r - size - 1, c - size - 1))
                size++;
            if (size >= 1) cnt[size]++;  // only a centre has all four diagonal neighbours black
        }
    return cnt;
}
// snippet:end

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    vector<int> cnt = countCrosses(g);
    int n = min(h, w);
    for (int s = 1; s <= n; s++) cout << cnt[s] << (s < n ? ' ' : '\n');
}
