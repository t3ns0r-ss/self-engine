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

int groupsOf(int n, const vector<pair<int, int>>& edges, int from) {  // brute force: walk the graph of edges from..end
    vector<int> label(n + 1, 0);
    int count = 0;
    for (int s = 1; s <= n; s++) {
        if (label[s]) continue;
        label[s] = ++count;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (size_t i = from; i < edges.size(); i++) {
                int v = edges[i].first == u ? edges[i].second : (edges[i].second == u ? edges[i].first : 0);
                if (v && !label[v]) label[v] = count, stack.push_back(v);
            }
        }
    }
    return count;
}

int main() {
    // P1: the path 1-2-3-4 loses the edges 2-3, 1-2, 3-4 in this order; groups after each removal.
    {
        vector<pair<int, int>> removed = {{2, 3}, {1, 2}, {3, 4}};
        int m = removed.size();
        string brute, method;
        for (int i = 1; i <= m; i++) brute += (i > 1 ? "," : "") + to_string(groupsOf(4, removed, i));
        vector<int> answer(m + 1);
        Dsu dsu(5);
        int count = 4;
        for (int i = m; i >= 1; i--) {
            answer[i] = count;
            if (dsu.unite(removed[i - 1].first, removed[i - 1].second)) count--;
        }
        for (int i = 1; i <= m; i++) method += (i > 1 ? "," : "") + to_string(answer[i]);
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    // N1: arrows 1->2, 3->2, 1->4; after the arrow 1->4 is removed, can vertex 1 still REACH vertex 3 along the arrows?
    // The union treats every arrow as a two-way link, so it says yes (1 and 3 are linked through 2).
    {
        vector<pair<int, int>> arrows = {{1, 4}, {1, 2}, {3, 2}};  // the first one is removed
        vector<bool> reach(5, false);
        reach[1] = true;
        vector<int> stack = {1};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (size_t i = 1; i < arrows.size(); i++)
                if (arrows[i].first == u && !reach[arrows[i].second]) reach[arrows[i].second] = true, stack.push_back(arrows[i].second);
        }
        Dsu dsu(5);
        for (size_t i = 1; i < arrows.size(); i++) dsu.unite(arrows[i].first, arrows[i].second);
        cout << "N1 brute=" << (reach[3] ? "yes" : "no") << " method=" << (dsu.find(1) == dsu.find(3) ? "yes" : "no") << "\n";
    }
}
