#include <bits/stdc++.h>
using namespace std;

// The best sum of a path in a tree: a top vertex joins its two best child paths.
int main() {
    // P1 and P2 use the tree 0-1, 0-2, 2-3, 2-4.
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    int n = 5;
    vector<vector<int>> adj(n);
    for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
    auto bestPathMethod = [&](vector<long long> w) {
        long long best = LLONG_MIN;
        function<long long(int, int)> go = [&](int v, int p) {
            long long top1 = 0, top2 = 0;
            for (int u : adj[v])
                if (u != p) {
                    long long d = max(0LL, go(u, v));
                    if (d > top1) top2 = top1, top1 = d;
                    else top2 = max(top2, d);
                }
            best = max(best, w[v] + top1 + top2);
            return w[v] + top1;
        };
        go(0, -1);
        return best;
    };
    auto bestPathBrute = [&](vector<long long> w) {
        long long best = LLONG_MIN;
        for (int s = 0; s < n; s++) {
            function<void(int, int, long long)> go = [&](int v, int p, long long sum) {
                sum += w[v];
                best = max(best, sum);
                for (int u : adj[v])
                    if (u != p) go(u, v, sum);
            };
            go(s, -1, 0);
        }
        return best;
    };
    vector<long long> w1 = {-2, 5, 1, 3, -4}, w2 = {-3, -1, -2, -9, -5};
    cout << "P1 brute=" << bestPathBrute(w1) << " method=" << bestPathMethod(w1) << "\n";
    cout << "P2 brute=" << bestPathBrute(w2) << " method=" << bestPathMethod(w2) << "\n";
    // N1: the best connected set (it may branch) is not a path. The star with a centre 1 and three leaves of value 5.
    vector<long long> w3 = {1, 5, 5, 5};
    long long total = 0;
    for (long long x : w3) total += x;  // all values are positive here, so the whole tree is the best connected set
    // the path method: the centre joins the two best leaves
    cout << "N1 brute=" << total << " method=" << 1 + 5 + 5 << "\n";
}
