// Keeps the set of cells reachable in exactly s steps, for s = 0..t.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long sx, sy, tx, ty, t;
        cin >> sx >> sy >> tx >> ty >> t;
        set<pair<long long, long long>> cur = {{sx, sy}};
        for (long long s = 0; s < t; s++) {
            set<pair<long long, long long>> nxt;
            for (auto [x, y] : cur) {
                nxt.insert({x + 1, y});
                nxt.insert({x - 1, y});
                nxt.insert({x, y + 1});
                nxt.insert({x, y - 1});
            }
            cur = nxt;
        }
        cout << (cur.count({tx, ty}) ? "YES" : "NO") << "\n";
    }
}
