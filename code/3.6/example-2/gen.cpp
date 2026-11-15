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
    int n = randInt(2, (randInt(0, 3) == 0) ? 120 : 15);
    // choose disjoint segments: mark random cut points in 1..n and keep some of the pieces
    vector<pair<int, int>> segs;
    int pos = 1;
    while (pos <= n && (int)segs.size() < 10) {
        int len = randInt(1, max(1, n / 3));
        int r = min(n, pos + len - 1);
        if (randInt(0, 1) == 0) segs.push_back({pos, r});
        pos = r + 1 + randInt(0, 2);
    }
    if (segs.empty()) segs.push_back({1, 1});
    shuffle(segs.begin(), segs.end(), rng);
    cout << n << " " << segs.size() << "\n";
    for (auto [l, r] : segs) cout << l << " " << r << "\n";
}
