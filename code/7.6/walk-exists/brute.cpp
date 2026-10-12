#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, from, to;
    long long length;
    cin >> n >> m >> length;
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) cin >> a >> b;
    cin >> from >> to;
    set<int> now = {from};  // the vertices reachable by a walk of the current length
    for (long long step = 0; step < length; step++) {
        set<int> next;
        for (int u : now)
            for (auto [a, b] : edges)
                if (a == u) next.insert(b);
        now = next;
    }
    cout << (now.count(to) ? "yes" : "no") << "\n";
}
