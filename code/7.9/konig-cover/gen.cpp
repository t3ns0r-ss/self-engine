#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int L = randInt(1, 7), R = randInt(1, 7);
    set<pair<int, int>> edges;
    int want = randInt(0, L * R);
    while ((int)edges.size() < want) edges.insert({randInt(1, L), randInt(1, R)});
    cout << L << " " << R << " " << edges.size() << "\n";
    for (auto [u, v] : edges) cout << u << " " << v << "\n";
}
