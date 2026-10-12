#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1);
    }
    vector<int> path = {0}, best;
    function<void(int)> go = [&](int v) {
        if (v == n - 1) {
            if (best.empty() || path.size() > best.size()) best = path;
            else if (path.size() == best.size()) {
                vector<int> a(path.rbegin(), path.rend()), b(best.rbegin(), best.rend());
                if (a < b) best = path;
            }
        }
        for (int u : out[v]) path.push_back(u), go(u), path.pop_back();
    };
    go(0);
    if (best.empty()) return cout << "IMPOSSIBLE\n", 0;
    cout << best.size() << "\n";
    for (size_t i = 0; i < best.size(); i++) cout << best[i] + 1 << (i + 1 < best.size() ? " " : "\n");
}
