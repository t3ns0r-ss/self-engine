#include <bits/stdc++.h>
using namespace std;

// For each road, cut it, walk from one end to find the size of that side, and multiply.
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& e : edges) cin >> e.first >> e.second;
    for (int cut = 0; cut + 1 < n; cut++) {
        vector<bool> seen(n + 1, false);
        vector<int> stack = {edges[cut].first};
        seen[edges[cut].first] = true;
        long long side = 0;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            side++;
            for (int i = 0; i + 1 < n; i++) {
                if (i == cut) continue;
                int v = edges[i].first == u ? edges[i].second : (edges[i].second == u ? edges[i].first : 0);
                if (v && !seen[v]) seen[v] = true, stack.push_back(v);
            }
        }
        cout << side * (n - side) << (cut + 2 < n ? " " : "\n");
    }
    if (n == 1) cout << "\n";
}
