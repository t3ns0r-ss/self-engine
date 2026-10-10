#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.2. Replace every '.' by the number of '#' among its 8 neighbours; every access is bounds-checked.
vector<string> countMines(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    vector<string> out = g;
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (g[r][c] == '#') continue;
            int mines = 0;
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;  // the cell itself is not a neighbour
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < h && nc >= 0 && nc < w && g[nr][nc] == '#') mines++;
                }
            out[r][c] = char('0' + mines);
        }
    return out;
}
// snippet:end

int main() {
    for (vector<string> g : {vector<string>{".#.", "...", "#.."}, vector<string>{"."}}) {
        for (auto& row : g) cout << row << ' ';
        cout << "->";
        for (auto& row : countMines(g)) cout << ' ' << row;
        cout << '\n';
    }
    mt19937 rng(3);
    for (int round = 0; round < 500; round++) {  // against the same count on a grid padded with a border of '.'
        int h = rng() % 4 + 1, w = rng() % 4 + 1;
        vector<string> g(h, string(w, '.'));
        for (auto& row : g) for (char& ch : row) ch = rng() % 2 ? '#' : '.';
        vector<string> p(h + 2, string(w + 2, '.'));
        for (int r = 0; r < h; r++) for (int c = 0; c < w; c++) p[r + 1][c + 1] = g[r][c];
        vector<string> got = countMines(g);
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++) {
                if (g[r][c] == '#') { if (got[r][c] != '#') return 1; continue; }
                int m = 0;
                for (int dr = 0; dr < 3; dr++) for (int dc = 0; dc < 3; dc++) m += p[r + dr][c + dc] == '#';
                if (got[r][c] != char('0' + m)) return 1;
            }
    }
}
