#include <bits/stdc++.h>
using namespace std;

// Breadth-first search over the sets of vertices that remain: delete one leaf at a time until vertex 1 is gone.
int main() {
    int n;
    cin >> n;
    vector<int> neighbours(n, 0);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        neighbours[a - 1] |= 1 << (b - 1);
        neighbours[b - 1] |= 1 << (a - 1);
    }
    map<int, int> dist;
    queue<int> q;
    int start = (1 << n) - 1;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int state = q.front();
        q.pop();
        if (!(state & 1)) { cout << dist[state] << "\n"; return 0; }
        for (int v = 0; v < n; v++) {
            if (!(state >> v & 1) || __builtin_popcount(neighbours[v] & state) > 1) continue;  // not a leaf of what is left
            int next = state & ~(1 << v);
            if (!dist.count(next)) dist[next] = dist[state] + 1, q.push(next);
        }
    }
}
