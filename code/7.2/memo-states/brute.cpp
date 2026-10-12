#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[n] = 0, q.push(n);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == 0) return cout << dist[0] << "\n", 0;
        vector<int> to = {v - 1};
        if (v % 2 == 0) to.push_back(v / 2);
        if (v % 3 == 0) to.push_back(v / 3);
        for (int u : to)
            if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
    }
}
