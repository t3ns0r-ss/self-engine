#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m);
    for (int i = 0; i < m; i++) cin >> ea[i] >> eb[i], ea[i]--, eb[i]--;
    vector<char> done(n, 0);
    vector<int> order;
    for (int step = 0; step < n; step++) {
        int pick = -1;
        for (int v = 0; v < n && pick < 0; v++) {
            if (done[v]) continue;
            bool free = true;
            for (int i = 0; i < m; i++) free = free && !(eb[i] == v && !done[ea[i]]);
            if (free) pick = v;
        }
        if (pick < 0) return cout << "IMPOSSIBLE\n", 0;
        done[pick] = 1, order.push_back(pick);
    }
    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? " " : "\n");
}
