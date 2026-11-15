#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long M;
    cin >> n >> M;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), adj[b - 1].push_back(a - 1);
    }
    for (int r = 0; r < n; r++) {
        function<long long(int, int)> go = [&](int v, int p) {
            long long x = 1 % M;
            for (int u : adj[v])
                if (u != p) x = x * ((go(u, v) + 1) % M) % M;
            return x;
        };
        cout << go(r, -1) << "\n";
    }
}
