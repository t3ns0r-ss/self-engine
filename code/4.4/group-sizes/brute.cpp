#include <bits/stdc++.h>
using namespace std;

// After every event, walk the graph of all friendships so far from scratch.
int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> events(q);
    for (auto& e : events) cin >> e.first >> e.second;
    for (int i = 0; i < q; i++) {
        vector<bool> seen(n + 1, false);
        vector<int> stack = {events[i].first};
        seen[events[i].first] = true;
        int size = 0;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            size++;
            for (int j = 0; j <= i; j++) {
                int v = events[j].first == u ? events[j].second : (events[j].second == u ? events[j].first : 0);
                if (v && !seen[v]) seen[v] = true, stack.push_back(v);
            }
        }
        cout << size << (i + 1 < q ? " " : "\n");
    }
    if (q == 0) cout << "\n";
}
