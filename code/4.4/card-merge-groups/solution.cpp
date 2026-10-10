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

// Brute force: walk the graph of the edges present, from scratch, for every question.
vector<int> componentOf(int n, const set<pair<int, int>>& edges) {
    vector<int> label(n + 1, 0);
    int next = 0;
    for (int s = 1; s <= n; s++) {
        if (label[s]) continue;
        label[s] = ++next;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto [a, b] : edges) {
                int v = a == u ? b : (b == u ? a : 0);
                if (v && !label[v]) label[v] = next, stack.push_back(v);
            }
        }
    }
    return label;
}

int main() {
    // P1: 6 users; after each of the events "become friends" print the size of the group of the first user.
    {
        vector<pair<int, int>> events = {{1, 2}, {3, 4}, {2, 3}, {5, 6}};
        Dsu dsu(7);
        set<pair<int, int>> present;
        string brute, method;
        for (auto [a, b] : events) {
            present.insert({a, b});
            auto label = componentOf(6, present);
            brute += (brute.empty() ? "" : ",") + to_string(count(label.begin() + 1, label.end(), label[a]));
            dsu.unite(a, b);
            method += (method.empty() ? "" : ",") + to_string(dsu.size[dsu.find(a)]);
        }
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    // N1: the events also contain "stop being friends". The structure of unite calls cannot split a group, so it ignores them.
    {
        struct Op { char type; int a, b; };
        vector<Op> ops = {{'+', 1, 2}, {'+', 2, 3}, {'-', 1, 2}};
        set<pair<int, int>> present;
        Dsu dsu(4);
        for (auto o : ops) {
            if (o.type == '+') present.insert({o.a, o.b}), dsu.unite(o.a, o.b);
            else present.erase({o.a, o.b});  // the brute force removes the edge; the union cannot
        }
        auto label = componentOf(3, present);
        cout << "N1 brute=" << (label[1] == label[3] ? "yes" : "no") << " method=" << (dsu.find(1) == dsu.find(3) ? "yes" : "no") << "\n";
    }
}
