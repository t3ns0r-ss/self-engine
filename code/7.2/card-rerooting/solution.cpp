#include <bits/stdc++.h>
using namespace std;

int main() {
    // The tree 0-1, 0-2, 2-3, 2-4; P1: the sum of the distances from the vertex 2; P2: connected black sets that contain the vertex 1.
    int n = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<vector<int>> adj(n);
    for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
    auto distances = [&](int s) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0, q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v])
                if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
        }
        return dist;
    };
    {
        long long brute = 0;
        for (int d : distances(2)) brute += d;
        // rerooting from the root 0: answer[0] = 0 + 1 + 1 + 2 + 2 = 6; answer[2] = answer[0] + n - 2 * size[2] = 6 + 5 - 6
        long long method = 6 + 5 - 2 * 3;
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    {
        // connected sets of black vertices that contain the vertex 1, by trying all subsets
        long long brute = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!(mask >> 1 & 1)) continue;
            vector<int> seen(n, 0), stack = {1};
            seen[1] = 1;
            int reached = 1;
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                for (int u : adj[v])
                    if ((mask >> u & 1) && !seen[u]) seen[u] = 1, reached++, stack.push_back(u);
            }
            brute += reached == __builtin_popcount(mask);
        }
        // rerooting: up[1] = (up[0] + 1) * (down[2] + 1) = 1 * 5 = 5, down[1] = 1, answer = down * (up + 1) = 6
        long long method = 1 * (5 + 1);
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: the farthest vertex from every vertex, with the update "answer[c] = max(down[c], answer[p] + 1)", on the tree
        // 0-1, 0-2, 1-3 (the path 3-1-0-2): the best way out of 0 goes through 1, so it cannot be reused for 1.
        int m = 4;
        vector<vector<int>> a2(m);
        for (auto [x, y] : vector<pair<int, int>>{{0, 1}, {0, 2}, {1, 3}}) a2[x].push_back(y), a2[y].push_back(x);
        vector<int> dist(m, -1);
        queue<int> q;
        dist[1] = 0, q.push(1);
        int brute = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            brute = max(brute, dist[v]);
            for (int u : a2[v])
                if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
        }
        int down1 = 1, answer0 = 2;  // the height below the vertex 1, and the farthest distance from the root 0 (to the vertex 3)
        int method = max(down1, answer0 + 1);
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
