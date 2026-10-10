#include <bits/stdc++.h>
using namespace std;

// Label propagation: every vertex starts with its own label; each edge copies the smaller label to both ends until nothing changes.
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
    map<int, int> count;
    for (int v = 1; v <= n; v++) count[label[v]]++;
    vector<int> sizes;
    for (auto [l, c] : count) sizes.push_back(c);
    sort(sizes.begin(), sizes.end());
    cout << sizes.size() << "\n";
    for (size_t i = 0; i < sizes.size(); i++) cout << (i ? " " : "") << sizes[i];
    cout << "\n";
}
