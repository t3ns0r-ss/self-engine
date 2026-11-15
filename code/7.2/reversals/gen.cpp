#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9);
    int shape = randInt(0, 3);  // random, path, star, all edges toward vertex 1
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int p = shape == 1 ? i - 1 : shape == 2 ? 0 : randInt(0, i - 1);
        int a = label[i], b = label[p];
        if (shape == 3 || randInt(0, 1)) swap(a, b);  // a -> b
        edges.push_back({a, b});
    }
    shuffle(edges.begin(), edges.end(), rng);
    printf("%d\n", n);
    for (auto [a, b] : edges) printf("%d %d\n", a, b);
}
