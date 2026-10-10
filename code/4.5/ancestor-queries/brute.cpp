#include <bits/stdc++.h>
using namespace std;

// Climb from v to the root through the parents and look for u.
int main() {
    int n;
    cin >> n;
    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        bool found = false;
        for (int x = v; x != 0; x = parent[x]) if (x == u) found = true;
        cout << (found ? "YES" : "NO") << "\n";
    }
}
