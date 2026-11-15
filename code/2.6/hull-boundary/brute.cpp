#include <bits/stdc++.h>
using namespace std;

// Brute force: a point is on the boundary of the hull exactly when some line through it has all the points on one closed side.
// The direction of such a line can be taken along the line to another point.
int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    vector<pair<long long, long long>> ans;
    for (int k = 0; k < n; k++) {
        bool on = n <= 2;
        for (int j = 0; j < n && !on; j++) {
            if (j == k) continue;
            for (int sgn = -1; sgn <= 1 && !on; sgn += 2) {
                long long dx = sgn * (x[j] - x[k]), dy = sgn * (y[j] - y[k]);
                bool allLeft = true;
                for (int m = 0; m < n; m++)
                    if (dx * (y[m] - y[k]) - dy * (x[m] - x[k]) < 0) allLeft = false;
                if (allLeft) on = true;
            }
        }
        if (on) ans.push_back({x[k], y[k]});
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto& p : ans) cout << p.first << " " << p.second << "\n";
}
