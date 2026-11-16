#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    int seed = atoi(argv[1]);
    mt19937 rng(seed);
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    vector<array<int, 3>> edges;
    int n, s, t;
    if (seed % 2 == 0) {
        // Any graph: repeated edges and edges in both directions are allowed, no self-loops.
        n = randInt(2, 8);
        int m = randInt(0, 14), maxCap = randInt(1, 6);
        s = randInt(1, n);
        t = randInt(1, n);
        while (t == s) t = randInt(1, n);
        for (int i = 0; i < m; i++) {
            int u = randInt(1, n), v = randInt(1, n);
            while (v == u) v = randInt(1, n);
            edges.push_back({u, v, randInt(1, maxCap)});
        }
    } else {
        // Layered graph s -> first layer -> second layer -> t, with small capacities. Several paths of equal length compete for the same
        // edges, so a flow that is blocked without being maximum is easy to produce (a missing reverse edge shows here).
        n = randInt(4, 8);
        s = 1;
        t = n;
        vector<int> layer(n + 1, 0);
        for (int v = 2; v < n; v++) layer[v] = randInt(1, 2);
        layer[s] = 0;
        layer[t] = 3;
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                if (layer[v] == layer[u] + 1 && randInt(0, 3) > 0) edges.push_back({u, v, randInt(1, 2)});
        shuffle(edges.begin(), edges.end(), rng);
    }
    cout << n << " " << edges.size() << " " << s << " " << t << "\n";
    for (auto& e : edges) cout << e[0] << " " << e[1] << " " << e[2] << "\n";
}
