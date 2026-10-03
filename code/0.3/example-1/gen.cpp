// Places random crosses that fit in the grid and do not touch (not even at a corner).
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int h = randInt(3, 12), w = randInt(3, 12);
    vector<string> g(h, string(w, '.'));
    for (int tries = 0; tries < 30; tries++) {
        int n = randInt(1, 3), a = randInt(0, h - 1), b = randInt(0, w - 1);
        vector<pair<int, int>> cells = {{a, b}};
        for (int d = 1; d <= n; d++)
            for (int sa : {-1, 1})
                for (int sb : {-1, 1}) cells.push_back({a + sa * d, b + sb * d});
        bool ok = true;
        for (auto [r, c] : cells) {
            if (r < 0 || r >= h || c < 0 || c >= w) ok = false;
            for (int dr = -1; dr <= 1 && ok; dr++)  // no black cell in the 3x3 block around any new cell
                for (int dc = -1; dc <= 1; dc++) {
                    int rr = r + dr, cc = c + dc;
                    if (rr >= 0 && rr < h && cc >= 0 && cc < w && g[rr][cc] == '#') ok = false;
                }
        }
        if (ok)
            for (auto [r, c] : cells) g[r][c] = '#';
    }
    cout << h << " " << w << "\n";
    for (auto& row : g) cout << row << "\n";
}
