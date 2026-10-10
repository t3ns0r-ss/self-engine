#include <bits/stdc++.h>
using namespace std;

// Label propagation gives every city the smallest city number of its group; the first cities of the groups, in increasing order,
// are joined one after the other.
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto [a, b] : edges) {
            int low = min(label[a], label[b]);
            if (label[a] != low || label[b] != low) {
                label[a] = label[b] = low;
                changed = true;
            }
        }
    }
    vector<int> firsts;
    for (int v = 1; v <= n; v++)
        if (label[v] == v) firsts.push_back(v);
    cout << firsts.size() - 1 << "\n";
    for (size_t i = 1; i < firsts.size(); i++) cout << firsts[i - 1] << " " << firsts[i] << "\n";
}
