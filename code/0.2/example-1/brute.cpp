// Fills the spiral cell by cell, layer by layer, in the order of the picture, up to size 40.
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int S = 40;
    vector<vector<long long>> g(S + 1, vector<long long>(S + 1));
    long long v = 1;
    g[1][1] = v++;
    for (int m = 2; m <= S; m++) {
        if (m % 2 == 0) {
            for (int y = 1; y <= m; y++) g[y][m] = v++;      // down column m
            for (int x = m - 1; x >= 1; x--) g[m][x] = v++;  // left along row m
        } else {
            for (int x = 1; x <= m; x++) g[m][x] = v++;      // right along row m
            for (int y = m - 1; y >= 1; y--) g[y][m] = v++;  // up column m
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int y, x;
        cin >> y >> x;
        cout << g[y][x] << "\n";
    }
}
