#include <bits/stdc++.h>
using namespace std;

// Component sizes: returns the label of each vertex (0 if skipped) with the edge and the vertex skipped.
vector<int> labels(int n, const vector<pair<int, int>>& edges, int skipEdge, int skipVertex) {
    vector<int> leader(n + 1);
    iota(leader.begin(), leader.end(), 0);
    function<int(int)> find = [&](int x) { return leader[x] == x ? x : leader[x] = find(leader[x]); };
    for (int i = 0; i < (int)edges.size(); i++)
        if (i != skipEdge && edges[i].first != skipVertex && edges[i].second != skipVertex) leader[find(edges[i].first)] = find(edges[i].second);
    vector<int> label(n + 1, 0);
    for (int v = 1; v <= n; v++)
        if (v != skipVertex) label[v] = find(v);
    return label;
}
int pieces(int n, const vector<pair<int, int>>& edges, int skipEdge, int skipVertex) {
    auto label = labels(n, edges, skipEdge, skipVertex);
    set<int> distinct;
    for (int v = 1; v <= n; v++)
        if (label[v]) distinct.insert(label[v]);
    return distinct.size();
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    int base = pieces(n, edges, -1, -1);
    vector<int> leader(n + 1);
    iota(leader.begin(), leader.end(), 0);
    function<int(int)> find = [&](int x) { return leader[x] == x ? x : leader[x] = find(leader[x]); };
    for (int i = 0; i < m; i++)
        if (pieces(n, edges, i, -1) == base) leader[find(edges[i].first)] = find(edges[i].second);
    map<int, int> size;
    for (int v = 1; v <= n; v++) size[find(v)]++;
    vector<int> sizes;
    for (auto [r, s] : size) sizes.push_back(s);
    sort(sizes.begin(), sizes.end());
    cout << sizes.size() << "\n";
    for (size_t i = 0; i < sizes.size(); i++) cout << sizes[i] << (i + 1 < sizes.size() ? ' ' : '\n');
}
