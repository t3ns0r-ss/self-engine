#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.2. Indexing by value: minw[t] = the least weight of a subset with total value exactly t; the answer is the
// largest t with minw[t] <= W. The weights may be huge.
int valueIndexed(const vector<long long>& w, const vector<int>& v, long long W) {
    int V = accumulate(v.begin(), v.end(), 0);
    const long long INF = LLONG_MAX / 2;
    vector<long long> minw(V + 1, INF);
    minw[0] = 0;
    for (size_t i = 0; i < w.size(); i++)
        for (int t = V; t >= v[i]; t--) minw[t] = min(minw[t], minw[t - v[i]] + w[i]);
    int answer = 0;
    for (int t = 0; t <= V; t++) if (minw[t] <= W) answer = t;
    return answer;
}
// snippet:end

int main() {
    cout << "weights 5 4 3, values 3 2 2, capacity 7: " << valueIndexed({5, 4, 3}, {3, 2, 2}, 7) << '\n';
    cout << "weights 10^9 8·10^8 3·10^8, values 3 2 2, capacity 10^9: " << valueIndexed({1000000000, 800000000, 300000000}, {3, 2, 2}, 1000000000) << '\n';
    mt19937 rng(22);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 8;
        vector<long long> w(n);
        vector<int> v(n);
        for (int i = 0; i < n; i++) w[i] = 1 + rng() % 1000000000, v[i] = 1 + rng() % 6;
        long long W = 1 + rng() % 2000000000LL;
        int best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long ww = 0;
            int vv = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) ww += w[i], vv += v[i];
            if (ww <= W) best = max(best, vv);
        }
        if (best != valueIndexed(w, v, W)) return 1;
    }
}
