#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (parent[x] != x) parent[x] = parent[parent[x]], x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main() {
    vector<array<long long, 3>> roads = {{1, 2, 4}, {2, 3, 6}, {1, 3, 9}, {3, 4, 2}};
    auto sorted = roads;
    sort(sorted.begin(), sorted.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    // P1: the smallest possible largest road on a trip from town 1 to town 4. Brute force: try each limit with a walk.
    {
        long long brute = -1;
        for (long long limit = 1; limit <= 9 && brute < 0; limit++) {
            vector<bool> seen(5, false);
            vector<int> stack = {1};
            seen[1] = true;
            while (!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                for (auto [a, b, w] : roads) {
                    if (w > limit) continue;
                    int v = a == u ? b : (b == u ? a : 0);
                    if (v && !seen[v]) seen[v] = true, stack.push_back(v);
                }
            }
            if (seen[4]) brute = limit;
        }
        Dsu dsu(5);
        long long method = -1;
        for (auto [a, b, w] : sorted) {
            dsu.unite(a, b);
            if (dsu.find(1) == dsu.find(4)) { method = w; break; }
        }
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    // P2: the number of pairs of towns that have a trip using only roads of length at most 5. Brute force: test every pair with a walk.
    {
        long long brute = 0;
        for (int s = 1; s <= 4; s++)
            for (int t = s + 1; t <= 4; t++) {
                vector<bool> seen(5, false);
                vector<int> stack = {s};
                seen[s] = true;
                while (!stack.empty()) {
                    int u = stack.back();
                    stack.pop_back();
                    for (auto [a, b, w] : roads) {
                        if (w > 5) continue;
                        int v = a == u ? b : (b == u ? a : 0);
                        if (v && !seen[v]) seen[v] = true, stack.push_back(v);
                    }
                }
                brute += seen[t];
            }
        Dsu dsu(5);
        long long method = 0;
        for (auto [a, b, w] : sorted) {
            if (w > 5) break;
            int x = dsu.find(a), y = dsu.find(b);
            if (x != y) method += (long long)dsu.size[x] * dsu.size[y], dsu.unite(a, b);  // every pair across the two groups is new
        }
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    // N1: the same question on ONE-WAY roads 1->2 (1), 3->2 (1): can town 1 reach town 3 along the arrows, and with which largest road?
    // The union treats the arrows as two-way, so it finds 1 (when 1 and 3 become linked), but along the arrows there is no trip.
    {
        vector<array<long long, 3>> arrows = {{1, 2, 1}, {3, 2, 1}};
        vector<bool> seen(4, false);
        vector<int> stack = {1};
        seen[1] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto [a, b, w] : arrows) if (a == u && !seen[b]) seen[b] = true, stack.push_back(b);
        }
        Dsu dsu(4);
        long long method = -1;
        for (auto [a, b, w] : arrows) {
            dsu.unite(a, b);
            if (dsu.find(1) == dsu.find(3)) { method = w; break; }
        }
        cout << "N1 brute=" << (seen[3] ? string("possible") : string("impossible")) << " method=" << method << "\n";
    }
}
