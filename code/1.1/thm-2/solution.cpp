#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.2. The smallest difference between two elements, and the smallest spread of k chosen elements:
// both are found among neighbours in sorted order.
pair<long long, long long> closestValues(vector<long long> a, int k) {
    sort(a.begin(), a.end());
    long long minDiff = LLONG_MAX, minSpread = LLONG_MAX;
    for (int i = 0; i + 1 < (int)a.size(); i++) minDiff = min(minDiff, a[i + 1] - a[i]);
    for (int i = 0; i + k - 1 < (int)a.size(); i++) minSpread = min(minSpread, a[i + k - 1] - a[i]);
    return {minDiff, minSpread};
}
// snippet:end

int main() {
    auto r = closestValues({10, 1, 7, 3, 8}, 3);
    cout << "10 1 7 3 8, k = 3: smallest difference " << r.first << ", smallest spread of 3 elements " << r.second << '\n';
    r = closestValues({5, 5, 9}, 2);
    cout << "5 5 9, k = 2: smallest difference " << r.first << ", smallest spread of 2 elements " << r.second << '\n';
    mt19937 rng(8);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 6 + 2, k = rng() % n + 1;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 20;
        long long bd = LLONG_MAX, bs = LLONG_MAX;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) bd = min(bd, llabs(a[i] - a[j]));
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != k) continue;
            long long lo = LLONG_MAX, hi = LLONG_MIN;
            for (int i = 0; i < n; i++) if (mask >> i & 1) lo = min(lo, a[i]), hi = max(hi, a[i]);
            bs = min(bs, hi - lo);
        }
        if (closestValues(a, k) != make_pair(bd, bs)) return 1;
    }
}
