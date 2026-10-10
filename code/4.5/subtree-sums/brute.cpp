#include <bits/stdc++.h>
using namespace std;

// For each folder, add up the files of every folder whose chain of parents passes through it.
int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    for (int v = 1; v <= n; v++) {
        long long total = 0;
        for (int u = 1; u <= n; u++)
            for (int x = u; x != 0; x = parent[x])
                if (x == v) { total += a[u]; break; }
        cout << total << (v < n ? " " : "\n");
    }
}
