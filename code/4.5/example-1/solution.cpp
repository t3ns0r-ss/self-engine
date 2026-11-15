/*
Problem: AtCoder ABC 420 E, Reachability Query.
Input: N Q, then Q queries: "1 u v" adds an edge, "2 v" flips the colour of v (all vertices start white), "3 v" asks whether a black
vertex can be reached from v. Output: Yes or No for each query of type 3.
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
// Example 1. Disjoint set union that also keeps, at each leader, how many black vertices its group has. Vertices are 1..n.
vector<string> reachabilityAnswers(int n, const vector<array<int, 3>>& queries) {
    Dsu dsu(n + 1);
    vector<int> black(n + 1, 0);       // black[leader]: the number of black vertices in the group
    vector<bool> isBlack(n + 1, false);
    vector<string> answers;
    for (auto [type, u, v] : queries) {
        if (type == 1) {
            int total = black[dsu.find(u)] + black[dsu.find(v)];
            if (dsu.unite(u, v)) black[dsu.find(u)] = total;  // the merged group keeps the sum at its leader
        } else if (type == 2) {
            black[dsu.find(u)] += isBlack[u] ? -1 : 1;
            isBlack[u] = !isBlack[u];
        } else {
            answers.push_back(black[dsu.find(u)] > 0 ? "Yes" : "No");
        }
    }
    return answers;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<array<int, 3>> queries(q, {0, 0, 0});
    for (auto& x : queries) {
        cin >> x[0] >> x[1];
        if (x[0] == 1) cin >> x[2];
    }
    for (auto& a : reachabilityAnswers(n, queries)) cout << a << "\n";
}
