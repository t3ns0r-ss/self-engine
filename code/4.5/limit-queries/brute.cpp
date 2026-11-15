#include <bits/stdc++.h>
using namespace std;

// For every question, walk the graph of the roads with w <= L.
int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<long long, 3>> roads(m);
    for (auto& r : roads) cin >> r[0] >> r[1] >> r[2];
    while (q--) {
        long long s, t, limit;
        cin >> s >> t >> limit;
        vector<bool> seen(n + 1, false);
        vector<int> stack = {(int)s};
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto [a, b, w] : roads) {
                if (w > limit) continue;
                int v = a == u ? b : (b == u ? a : 0);
                if (v && !seen[v]) seen[v] = true, stack.push_back(v);
            }
        }
        cout << (seen[t] ? "YES" : "NO") << "\n";
    }
}
