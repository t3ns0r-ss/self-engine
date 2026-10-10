#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.3. Add v to a[l..r] for every update (0-based), then read the whole array: one running sum.
vector<long long> applyUpdates(int n, const vector<array<long long, 3>>& updates) {
    vector<long long> d(n + 1, 0);  // difference array; index n absorbs updates ending at n - 1
    for (auto [l, r, v] : updates) {
        d[l] += v;      // the value starts rising at l
        d[r + 1] -= v;  // and drops back after r
    }
    vector<long long> a(n);
    long long cur = 0;
    for (int i = 0; i < n; i++) a[i] = cur += d[i];
    return a;
}
// snippet:end

int main() {
    auto a = applyUpdates(5, {{1, 3, 2}, {2, 4, 5}});
    cout << "n = 5, add 2 on [1, 3], add 5 on [2, 4]:";
    for (long long x : a) cout << ' ' << x;
    cout << '\n';
    a = applyUpdates(5, {{0, 4, 3}});
    cout << "n = 5, add 3 on [0, 4]:";
    for (long long x : a) cout << ' ' << x;
    cout << '\n';
    mt19937 rng(3);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 8 + 1, q = rng() % 6;
        vector<array<long long, 3>> ups;
        vector<long long> brute(n, 0);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = l + rng() % (n - l);
            long long v = (long long)(rng() % 11) - 5;
            ups.push_back({l, r, v});
            for (int k = l; k <= r; k++) brute[k] += v;
        }
        if (applyUpdates(n, ups) != brute) return 1;
    }
}
