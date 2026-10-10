#include <bits/stdc++.h>
using namespace std;

// For every question of type 3, walk the graph of all edges added so far.
int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> edges;
    vector<bool> black(n + 1, false);
    while (q--) {
        int type, u, v = 0;
        cin >> type >> u;
        if (type == 1) cin >> v, edges.push_back({u, v});
        else if (type == 2) black[u] = !black[u];
        else {
            vector<bool> seen(n + 1, false);
            vector<int> stack = {u};
            seen[u] = true;
            bool found = false;
            while (!stack.empty()) {
                int x = stack.back();
                stack.pop_back();
                found |= black[x];
                for (auto [a, b] : edges) {
                    int y = a == x ? b : (b == x ? a : 0);
                    if (y && !seen[y]) seen[y] = true, stack.push_back(y);
                }
            }
            cout << (found ? "Yes" : "No") << "\n";
        }
    }
}
