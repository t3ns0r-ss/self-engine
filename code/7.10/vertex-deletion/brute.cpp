#include <bits/stdc++.h>
using namespace std;

// The maximum matching of the tree and of the tree without each vertex, by trying every subset of edges.
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    auto best = [&](int removed) {
        int result = 0;
        for (int mask = 0; mask < (1 << (n - 1)); mask++) {
            vector<int> used(n, 0);
            bool ok = true;
            for (int i = 0; i < n - 1 && ok; i++) {
                if (!(mask >> i & 1)) continue;
                auto [a, b] = edges[i];
                if (a == removed || b == removed || used[a] || used[b]) ok = false;
                used[a] = used[b] = 1;
            }
            if (ok) result = max(result, __builtin_popcount(mask));
        }
        return result;
    };
    int whole = best(-1), count = 0;
    for (int v = 0; v < n; v++) count += best(v) == whole;
    cout << count << "\n";
}
