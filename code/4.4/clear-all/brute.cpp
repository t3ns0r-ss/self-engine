#include <bits/stdc++.h>
using namespace std;

// Brute force: keep relaxing every medicine from every state until nothing improves (no priority queue, no order).
int main() {
    int k, m;
    cin >> k >> m;
    vector<long long> days(m);
    vector<int> cure(m), cause(m);
    for (int i = 0; i < m; i++) cin >> days[i] >> cure[i] >> cause[i];
    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(1 << k, INF);
    dist[(1 << k) - 1] = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int s = 0; s < (1 << k); s++) {
            if (dist[s] == INF) continue;
            for (int i = 0; i < m; i++) {
                int t = (s & ~cure[i]) | cause[i];
                if (dist[s] + days[i] < dist[t]) {
                    dist[t] = dist[s] + days[i];
                    changed = true;
                }
            }
        }
    }
    cout << (dist[0] == INF ? -1 : dist[0]) << "\n";
}
