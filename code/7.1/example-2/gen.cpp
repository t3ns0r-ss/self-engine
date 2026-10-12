#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 9);
    vector<int> label(n), degree(n + 1, 0);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    vector<array<int, 3>> edges;
    for (int i = 1; i < n; i++) {
        int a = label[i], b = label[randInt(0, i - 1)];
        edges.push_back({a, b, randInt(-9, 9)});
        degree[a]++, degree[b]++;
    }
    printf("%d\n", n);
    for (int v = 1; v <= n; v++) printf("%d%c", randInt(0, degree[v]), v < n ? ' ' : '\n');
    for (auto [a, b, w] : edges) printf("%d %d %d\n", a, b, w);
}
