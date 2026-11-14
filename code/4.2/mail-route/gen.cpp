#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 6);
    vector<pair<int, int>> streets;
    int kind = randInt(0, 3);
    if (kind == 0) {
        // Arbitrary streets: odd degrees and several components are common.
        int m = randInt(1, 7);
        for (int i = 0; i < m; i++) {
            int a = randInt(1, n), b = randInt(1, n);
            if (a == b) b = a % n + 1;
            streets.push_back({a, b});
        }
    } else {
        // A union of closed loops: every degree is even. Sometimes the loops are far from crossing 1.
        int loops = randInt(1, 2);
        for (int k = 0; k < loops && streets.size() < 7; k++) {
            int len = randInt(2, 4);
            vector<int> walk = {randInt(kind == 3 ? 2 : 1, n)};
            for (int i = 1; i < len; i++) {
                int v = randInt(1, n);
                if (v == walk.back()) v = v % n + 1;
                walk.push_back(v);
            }
            if (walk.back() != walk.front()) walk.push_back(walk.front());  // close the walk
            for (size_t i = 0; i + 1 < walk.size(); i++) streets.push_back({walk[i], walk[i + 1]});
        }
        if (streets.size() > 7) streets.resize(7);
        if (randInt(0, 3) == 0 && streets.size() > 1) streets.pop_back();  // now two odd crossings
    }
    cout << n << " " << streets.size() << "\n";
    for (auto [a, b] : streets) cout << a << " " << b << "\n";
}
