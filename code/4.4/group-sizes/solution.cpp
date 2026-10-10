/*
Problem: growing circles of friends.
Input: n q, then q lines "a b": users a and b become friends (a may equal b, and a pair may repeat).
Output: q numbers: after each event, the size of the group of friends (direct or through others) that a belongs to.
*/
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

// snippet:begin
// Theorem 4.4.1. After each event "a and b become friends", the size of the group of a. Users are 1..n.
vector<int> sizesAfterEach(int n, const vector<pair<int, int>>& events) {
    Dsu dsu(n + 1);
    vector<int> sizes;
    for (auto [a, b] : events) {
        dsu.unite(a, b);                      // false when they were friends already: nothing changes
        sizes.push_back(dsu.size[dsu.find(a)]);  // the size is kept at the leader
    }
    return sizes;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> events(q);
    for (auto& e : events) cin >> e.first >> e.second;
    auto sizes = sizesAfterEach(n, events);
    for (int i = 0; i < q; i++) cout << sizes[i] << (i + 1 < q ? " " : "\n");
    if (q == 0) cout << "\n";
}
