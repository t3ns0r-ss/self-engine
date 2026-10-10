#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the number of '#' among the neighbours of cell (0, 0) in
    //   .#.
    //   ...
    //   #..
    // Brute: pad the grid with a border of '.'. Method: bounds-checked access.
    vector<string> g = {".#.", "...", "#.."};
    vector<string> p(5, string(5, '.'));
    for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) p[r + 1][c + 1] = g[r][c];
    int padded = 0, checked = 0;
    for (int dr = 0; dr < 3; dr++) for (int dc = 0; dc < 3; dc++) if (dr != 1 || dc != 1) padded += p[dr][dc] == '#';
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++) {
            int nr = dr, nc = dc;
            if ((dr || dc) && nr >= 0 && nr < 3 && nc >= 0 && nc < 3 && g[nr][nc] == '#') checked++;
        }
    cout << "P1 brute=" << padded << " method=" << checked << '\n';
    // N1: a robot facing up (direction 0) turns left. Brute: direction 3. Method: (d - 1) % 4.
    int d = 0;
    cout << "N1 brute=" << (d + 3) % 4 << " method=" << (d - 1) % 4 << '\n';
    // N2: neighbours of the centre of a 3 x 3 grid of '#', where the loop does not skip the cell itself.
    int skip = 0, noSkip = 0;
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++) {
            noSkip++;
            if (dr || dc) skip++;
        }
    cout << "N2 brute=" << skip << " method=" << noSkip << '\n';
}
