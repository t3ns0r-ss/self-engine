#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) cin >> a >> b;
    vector<long long> ways(n + 1, 0);  // ways[v] = walks of the current length from the node 1 to v
    ways[1] = 1;
    for (long long step = 0; step < k; step++) {
        vector<long long> next(n + 1, 0);
        for (auto [a, b] : edges) next[b] = (next[b] + ways[a]) % 1000000007;
        ways = next;
    }
    cout << ways[n] << "\n";
}
