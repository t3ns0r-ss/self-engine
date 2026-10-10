#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.4.1. Disjoint set union with union by size and path halving. Vertices are 0..n-1.
struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {  // the leader of x's group
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];  // jump over the parent: the path gets shorter
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {  // true if a and b were in different groups
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;  // the smaller group goes under the larger one
        size[a] += size[b];
        return true;
    }
};
// snippet:end

int main() {
    {
        Dsu d(5);
        cout << "unite 0-1: " << d.unite(0, 1) << ", unite 2-3: " << d.unite(2, 3) << ", unite 1-0 again: " << d.unite(1, 0) << "\n";
        cout << "same group 0 and 3: " << (d.find(0) == d.find(3)) << ", unite 1-2: " << d.unite(1, 2) << ", same group 0 and 3: " << (d.find(0) == d.find(3)) << "\n";
        cout << "size of the group of 3: " << d.size[d.find(3)] << ", of 4: " << d.size[d.find(4)] << "\n";
    }
    {
        Dsu d(1 << 10);
        int successes = 0;
        for (int step = 1; step < (1 << 10); step *= 2)
            for (int i = 0; i + step < (1 << 10); i += 2 * step) successes += d.unite(i, i + step);
        int depth = 0;  // longest chain of parents after merging equal groups: the worst case for the depth
        for (int v = 0; v < (1 << 10); v++) {
            int x = v, steps = 0;
            while (d.parent[x] != x) x = d.parent[x], steps++;
            depth = max(depth, steps);
        }
        cout << "1024 vertices merged pairwise: " << successes << " successful unite calls, longest chain " << depth << " (log2 1024 = 10)\n";
    }
    // Check against a plain labelling: relabel a whole group on each edge.
    mt19937 rng(4401);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 10 + 1, q = rng() % 20;
        Dsu d(n);
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        int comps = n;
        for (int i = 0; i < q; i++) {
            int a = rng() % n, b = rng() % n;
            bool merged = label[a] != label[b];
            int from = label[b], to = label[a];
            for (int v = 0; v < n; v++) if (label[v] == from) label[v] = to;
            if (merged) comps--;
            if (d.unite(a, b) != merged) return 1;
        }
        int groups = 0;
        for (int v = 0; v < n; v++) {
            groups += d.find(v) == v;
            for (int u = 0; u < n; u++) if ((d.find(u) == d.find(v)) != (label[u] == label[v])) return 1;
            if (d.size[d.find(v)] != (int)count(label.begin(), label.end(), label[v])) return 1;
        }
        if (groups != comps) return 1;
    }
}
