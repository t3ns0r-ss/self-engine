#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 7);
    int s = randInt(1, n), t = randInt(1, n);
    while (t == s) t = randInt(1, n);
    set<pair<int, int>> edges;
    int want = randInt(0, 12);
    for (int tries = 0; tries < 50 && (int)edges.size() < want; tries++) {
        int u = randInt(1, n), v = randInt(1, n);
        if (u != v) edges.insert({u, v});
    }
    cout << n << " " << edges.size() << " " << s << " " << t << "\n";
    for (auto [u, v] : edges) cout << u << " " << v << "\n";
}
