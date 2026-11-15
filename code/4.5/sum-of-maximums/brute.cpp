#include <bits/stdc++.h>
using namespace std;

// For every pair, walk the tree from one city and track the largest toll on the way.
int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> roads(n - 1);
    for (auto& r : roads) cin >> r[0] >> r[1] >> r[2];
    long long total = 0;
    for (int s = 1; s <= n; s++) {
        vector<long long> largest(n + 1, -1);
        largest[s] = 0;
        vector<int> stack = {s};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto [a, b, w] : roads) {
                int v = a == u ? b : (b == u ? a : 0);
                if (v && largest[v] < 0) largest[v] = max(largest[u], w), stack.push_back(v);
            }
        }
        for (int t = s + 1; t <= n; t++) total += largest[t];
    }
    cout << total << "\n";
}
