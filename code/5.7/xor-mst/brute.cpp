#include <bits/stdc++.h>
using namespace std;

int main() {  // Prim's algorithm on the complete graph, O(n^2)
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<long long> dist(n, LLONG_MAX);
    vector<bool> used(n, false);
    dist[0] = 0;
    long long total = 0;
    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (u < 0 || dist[i] < dist[u])) u = i;
        used[u] = true;
        total += dist[u];
        for (int i = 0; i < n; i++)
            if (!used[i]) dist[i] = min<long long>(dist[i], a[u] ^ a[i]);
    }
    cout << total << "\n";
}
