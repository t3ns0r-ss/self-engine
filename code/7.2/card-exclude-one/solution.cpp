#include <bits/stdc++.h>
using namespace std;

int main() {
    // The tree 0-1, 0-2, 2-3, 2-4 with every edge of length 1.
    // P1: the largest distance from the vertex 1; P2: connected sets that contain the vertex 2, modulo 6;
    // N1: the sum of the distances from the vertex 2, where the two best values answer a different question.
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
        vector<int> from1 = distances(1);
        int brute = *max_element(from1.begin(), from1.end());
        // Rooted at 0: down[1] = down[3] = down[4] = 0, down[2] = 1, down[0] = 2. The ways out of 0 are 1 (to 1) and 2 (to 2):
        // b1 = 2, b2 = 1. The child 1 has down + 1 = 1, which is not b1, so up[1] = 1 + b1 = 3, and the answer is max(down[1], up[1]).
        int down1 = 0, b1 = 2, b2 = 1;
        int up1 = 1 + (down1 + 1 == b1 ? b2 : b1);
        cout << "P1 brute=" << brute << " method=" << max(down1, up1) << "\n";
    }
    {
        long long brute = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!(mask >> 2 & 1)) continue;
            vector<int> seen(n, 0), stack = {2};
            seen[2] = 1;
            int reached = 1;
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                for (int u : adj[v])
                    if ((mask >> u & 1) && !seen[u]) seen[u] = 1, reached++, stack.push_back(u);
            }
            brute += reached == __builtin_popcount(mask);
        }
        // Prefix and suffix products modulo 6: down[2] = (1 + 1)(1 + 1) = 4; up[2] = (up[0] + 1)(down[1] + 1) = 2;
        // the count is down[2] * (up[2] + 1) = 12, which is 0 modulo 6.
        long long M = 6, down2 = 4 % M, up2 = (0 + 1) * (0 + 1 + 1) % M;
        cout << "P2 brute=" << brute % M << " method=" << down2 * ((up2 + 1) % M) % M << "\n";
    }
    {
        vector<int> from2 = distances(2);
        int brute = accumulate(from2.begin(), from2.end(), 0);
        int method = *max_element(from2.begin(), from2.end());  // the largest way out, not the sum
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
