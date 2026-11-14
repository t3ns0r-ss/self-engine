#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    vector<pair<long long, long long>> lines;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long m, c;
            cin >> m >> c;
            lines.push_back({m, c});
        } else {
            long long x, best = LLONG_MAX;
            cin >> x;
            for (auto [m, c] : lines) best = min(best, m * x + c);
            if (lines.empty()) cout << "INF\n";
            else cout << best << "\n";
        }
    }
}
