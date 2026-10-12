#include <bits/stdc++.h>
using namespace std;

int main() {
    // The tree 0-1, 0-2, 2-3, 2-4 with values 1 -5 -5 10 10: the best connected set with k vertices that contains the root 0.
    int n = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<long long> w = {1, -5, -5, 10, 10};
    const long long NEG = LLONG_MIN / 4;
    auto brute = [&](int k) {
        long long best = NEG;
        for (int mask = 1; mask < (1 << n); mask++) {
            if (!(mask & 1) || __builtin_popcount(mask) != k) continue;
            vector<int> seen(n, 0), stack = {0};
            seen[0] = 1;
            int reached = 1;
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                for (auto [a, b] : edges) {
                    int u = a == v ? b : b == v ? a : -1;
                    if (u >= 0 && (mask >> u & 1) && !seen[u]) seen[u] = 1, reached++, stack.push_back(u);
                }
            }
            if (reached == k) {
                long long sum = 0;
                for (int v = 0; v < n; v++)
                    if (mask >> v & 1) sum += w[v];
                best = max(best, sum);
            }
        }
        return best;
    };
    // the tables of the method, by hand: the subtree of 2 is {2, 3, 4}
    vector<long long> d2 = {NEG, -5, 5, 15}, d1 = {NEG, -5};
    vector<long long> d0 = {NEG, 1};
    for (auto child : {d1, d2}) {
        vector<long long> merged(d0.size() + child.size() - 1, NEG);
        for (size_t a = 1; a < d0.size(); a++) {
            merged[a] = max(merged[a], d0[a]);
            for (size_t b = 1; b < child.size(); b++) merged[a + b] = max(merged[a + b], d0[a] + child[b]);
        }
        d0 = merged;
    }
    cout << "P1 brute=" << brute(3) << " method=" << d0[3] << "\n";
    cout << "P2 brute=" << brute(4) << " method=" << d0[4] << "\n";
    // N1: the question has no connectedness: the 3 largest of 1 -5 -5 10 10 add up to 21, but the tables give 6.
    vector<long long> sorted = w;
    sort(sorted.rbegin(), sorted.rend());
    cout << "N1 brute=" << sorted[0] + sorted[1] + sorted[2] << " method=" << d0[3] << "\n";
}
