#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) {
        return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo;
    };
    int H = randInt(1, 5), W = randInt(1, 5);
    if (H * W < 2) W = 2;
    vector<string> g(H, string(W, '.'));
    for (auto& row : g) for (auto& ch : row) if (randInt(0, 3) == 0) ch = '#';
    int s = randInt(0, H * W - 1), t = randInt(0, H * W - 1);
    while (t == s) t = randInt(0, H * W - 1);
    g[s / W][s % W] = 'S';
    g[t / W][t % W] = 'G';
    cout << H << " " << W << "\n";
    for (auto& row : g) cout << row << "\n";
}
