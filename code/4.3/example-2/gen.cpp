#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int h, w;
    do h = randInt(1, 7), w = randInt(1, 7); while (h * w < 2);
    int p = randInt(2, 9);
    vector<string> g(h, string(w, '.'));
    for (auto& row : g) for (auto& c : row) c = randInt(0, 9) < p ? '#' : '.';
    int sx = randInt(1, h), sy = randInt(1, w), tx, ty;
    do tx = randInt(1, h), ty = randInt(1, w); while (tx == sx && ty == sy);
    g[sx - 1][sy - 1] = g[tx - 1][ty - 1] = '.';
    cout << h << " " << w << "\n" << sx << " " << sy << "\n" << tx << " " << ty << "\n";
    for (auto& row : g) cout << row << "\n";
}
