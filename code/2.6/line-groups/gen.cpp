#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int side = randInt(1, 4);  // a small grid: many triples are collinear
    int maxN = (side + 1) * (side + 1);
    int n = randInt(1, min(8, maxN));
    set<pair<int, int>> used;
    vector<pair<int, int>> pts;
    while ((int)pts.size() < n) {
        pair<int, int> c = {randInt(0, side), randInt(0, side)};
        if (used.insert(c).second) pts.push_back(c);
    }
    cout << n << " " << randInt(1, min(n + 1, 5)) << "\n";
    for (auto& c : pts) cout << c.first << " " << c.second << "\n";
}
