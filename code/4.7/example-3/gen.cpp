#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 8);
    set<pair<int, int>> used;
    vector<pair<int, int>> edges;
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end(), rng);
    auto add = [&](int a, int b) {
        if (a != b && used.insert({min(a, b), max(a, b)}).second) edges.push_back({a, b});  // no repeated connections
    };
    for (int i = 1; i < n; i++) add(label[i], label[randInt(0, i - 1)]);
    for (int i = randInt(0, 4); i > 0; i--) add(randInt(0, n - 1), randInt(0, n - 1));
    shuffle(edges.begin(), edges.end(), rng);
    cout << n << " " << edges.size() << "\n";
    for (auto [a, b] : edges) cout << a << " " << b << "\n";
}
