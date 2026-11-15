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
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) edges.push_back({label[i], label[randInt(0, i - 1)]});
    shuffle(edges.begin(), edges.end(), rng);
    printf("%d %d\n", n, randInt(0, 1) ? randInt(2, 12) : 1000000000);
    for (auto [a, b] : edges) printf("%d %d\n", a, b);
}
