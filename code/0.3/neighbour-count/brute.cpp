// For each cell, checks every mine in the grid and counts those at distance 1 in both directions.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') {
                cout << '#';
                continue;
            }
            int mines = 0;
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++)
                    if (g[i][j] == '#' && abs(i - r) <= 1 && abs(j - c) <= 1) mines++;
            cout << mines;
        }
        cout << "\n";
    }
}
