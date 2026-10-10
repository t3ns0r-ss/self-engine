#include <bits/stdc++.h>
using namespace std;

// Walk from a to b, remembering the path by parents, and look for c on it.
int main() {
    int n, q;
    cin >> n >> q;
    vector<array<long long, 3>> edges(n - 1);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> parent(n + 1, -1);
        parent[a] = 0;
        vector<int> stack = {a};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto& e : edges) {
                int v = e[0] == u ? e[1] : (e[1] == u ? e[0] : 0);
                if (v && parent[v] < 0) parent[v] = u, stack.push_back(v);
            }
        }
        bool found = false;
        for (int x = b; x != 0; x = parent[x]) if (x == c) found = true;
        cout << (found ? "YES" : "NO") << "\n";
    }
}
