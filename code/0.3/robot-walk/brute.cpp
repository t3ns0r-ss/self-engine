// Spells out every direction by name, with the grid surrounded by a border of walls.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, r, c;
    cin >> h >> w >> r >> c;
    vector<string> g(h + 2, string(w + 2, '#'));
    for (int i = 1; i <= h; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= w; j++) g[i][j] = row[j - 1];
    }
    string cmd;
    cin >> cmd;
    r++, c++;
    string dir = "up";
    for (char ch : cmd) {
        if (ch == 'R') dir = dir == "up" ? "right" : dir == "right" ? "down" : dir == "down" ? "left" : "up";
        else if (ch == 'L') dir = dir == "up" ? "left" : dir == "left" ? "down" : dir == "down" ? "right" : "up";
        else if (dir == "up" && g[r - 1][c] != '#') r--;
        else if (dir == "down" && g[r + 1][c] != '#') r++;
        else if (dir == "left" && g[r][c - 1] != '#') c--;
        else if (dir == "right" && g[r][c + 1] != '#') c++;
    }
    cout << r - 1 << " " << c - 1 << "\n";
}
