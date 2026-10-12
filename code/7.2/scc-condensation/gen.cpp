#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8);
    vector<pair<int, int>> edges;
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
            if (a != b && randInt(1, 100) <= 20) edges.push_back({a, b});
    shuffle(edges.begin(), edges.end(), rng);
    printf("%d %d\n", n, (int)edges.size());
    for (auto [a, b] : edges) printf("%d %d\n", a, b);
}
