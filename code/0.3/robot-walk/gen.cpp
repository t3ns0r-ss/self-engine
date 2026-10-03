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
    int h = randInt(1, 5), w = randInt(1, 5);
    vector<string> g(h, string(w, '.'));
    for (auto& row : g)
        for (auto& ch : row)
            if (randInt(0, 3) == 0) ch = '#';
    int r = randInt(0, h - 1), c = randInt(0, w - 1);
    g[r][c] = '.';
    int n = randInt(1, 15);
    string cmd;
    for (int i = 0; i < n; i++) cmd += "FFLR"[randInt(0, 3)];
    cout << h << " " << w << " " << r << " " << c << "\n";
    for (auto& row : g) cout << row << "\n";
    cout << cmd << "\n";
}
