#include <bits/stdc++.h>
using namespace std;

// For every trip, find the path by a walk from a and add 1 to every road on it.
int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> roads(n - 1);
    for (auto& e : roads) cin >> e.first >> e.second;
    vector<long long> used(n - 1, 0);
    while (q--) {
        int a, b;
        cin >> a >> b;
        vector<int> viaRoad(n + 1, -2);  // the road by which each town was reached
        vector<int> from(n + 1, 0);
        viaRoad[a] = -1;
        vector<int> stack = {a};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int i = 0; i + 1 < n; i++) {
                int v = roads[i].first == u ? roads[i].second : (roads[i].second == u ? roads[i].first : 0);
                if (v && viaRoad[v] == -2) viaRoad[v] = i, from[v] = u, stack.push_back(v);
            }
        }
        for (int x = b; x != a; x = from[x]) used[viaRoad[x]]++;
    }
    for (int i = 0; i + 1 < n; i++) cout << used[i] << (i + 2 < n ? " " : "\n");
    if (n == 1) cout << "\n";
}
