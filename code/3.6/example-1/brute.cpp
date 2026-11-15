// Brute force: walk every right/down path by recursion and count those that avoid traps.
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> g;

long long walk(int r, int c) {
    if (r >= n || c >= n || g[r][c] == '*') return 0;
    if (r == n - 1 && c == n - 1) return 1;
    return walk(r + 1, c) + walk(r, c + 1);
}

int main() {
    cin >> n;
    g.resize(n);
    for (auto& row : g) cin >> row;
    cout << walk(0, 0) % 1'000'000'007 << "\n";
}
