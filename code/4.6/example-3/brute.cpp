#include <bits/stdc++.h>
using namespace std;

// For every question, test every vertex: is it at depth d, and is u among its ancestors?
int main() {
    int n;
    cin >> n;
    vector<int> parent(n + 1, 0), depth(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i], depth[i] = depth[parent[i]] + 1;
    int q;
    cin >> q;
    while (q--) {
        int u, d;
        cin >> u >> d;
        int count = 0;
        for (int v = 1; v <= n; v++) {
            if (depth[v] != d) continue;
            for (int x = v; x != 0; x = parent[x]) if (x == u) { count++; break; }
        }
        cout << count << "\n";
    }
}
