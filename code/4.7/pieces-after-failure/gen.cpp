#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 7), extra = randInt(0, 4);
    vector<pair<int, int>> edges;
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    for (int i = 1; i < n; i++) edges.push_back({label[i], label[randInt(0, i - 1)]});  // a random tree: the graph is connected
    for (int i = 0; i < extra && n > 1; i++) {
        int a = randInt(1, n), b = randInt(1, n);
        if (a != b) edges.push_back({a, b});  // extra roads, possibly parallel
    }
    shuffle(edges.begin(), edges.end(), rng);
    cout << n << " " << edges.size() << "\n";
    for (auto [a, b] : edges) cout << a << " " << b << "\n";
}
