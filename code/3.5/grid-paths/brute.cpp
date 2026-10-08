// Brute force: walk every right/down path by recursion and count those that avoid blocked cells.
#include <bits/stdc++.h>
using namespace std;

int h, w;
vector<string> g;

long long walk(int r, int c) {
    if (r >= h || c >= w || g[r][c] == '#') return 0;
    if (r == h - 1 && c == w - 1) return 1;
    return walk(r + 1, c) + walk(r, c + 1);
}

int main() {
    cin >> h >> w;
    g.resize(h);
    for (auto& row : g) cin >> row;
    cout << walk(0, 0) % 1'000'000'007 << "\n";
}
