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
    int H = randInt(1, 3), W = randInt(1, 3);
    int K = randInt(1, min(5, H * W + 1));
    if (H * W >= 8) K = min(K, 4);  // keeps (H*W)^(K+1) small for the brute force
    vector<string> g(H, string(W, '.'));
    int blockedPercent = randInt(0, 40);
    for (auto& row : g)
        for (auto& ch : row)
            if (randInt(1, 100) <= blockedPercent) ch = '#';
    g[randInt(0, H - 1)][randInt(0, W - 1)] = '.';  // at least one empty cell
    cout << H << " " << W << " " << K << "\n";
    for (auto& row : g) cout << row << "\n";
}
