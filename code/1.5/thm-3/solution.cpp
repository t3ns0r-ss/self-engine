#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.3. The fewest items whose sum reaches T (the largest first, -1 if impossible), and the largest value of at
// most W units from goods given as (value per unit, units).
int fewestItems(vector<int> v, int T) {
    sort(v.rbegin(), v.rend());
    int sum = 0;
    for (int k = 0; k < (int)v.size(); k++)
        if ((sum += v[k]) >= T) return k + 1;
    return -1;
}
long long bestUnits(vector<pair<int, int>> goods, int W) {
    sort(goods.rbegin(), goods.rend());  // most valuable units first
    long long total = 0;
    for (auto [value, units] : goods) {
        int take = min(units, W);
        total += (long long)take * value;
        W -= take;
    }
    return total;
}
// snippet:end

int main() {
    for (int T : {9, 11, 13}) {
        int k = fewestItems({5, 1, 4, 2}, T);
        cout << "values 5 1 4 2, target " << T << ": " << (k < 0 ? "none" : to_string(k) + " items") << '\n';
    }
    cout << "at most 5 units of (value 3, 4 units) and (value 5, 2 units): " << bestUnits({{3, 4}, {5, 2}}, 5) << '\n';
    mt19937 rng(3);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 6 + 1, T = rng() % 25 + 1;
        vector<int> v(n);
        for (int& x : v) x = rng() % 8 + 1;
        int best = -1;
        for (int mask = 0; mask < (1 << n); mask++) {
            int s = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s += v[i];
            if (s >= T && (best < 0 || __builtin_popcount(mask) < best)) best = __builtin_popcount(mask);
        }
        if (best != fewestItems(v, T)) return 1;
        vector<pair<int, int>> goods(n);
        for (auto& g : goods) g = {(int)(rng() % 6), (int)(rng() % 4)};
        int W = rng() % 8;
        vector<int> unitValues;  // every unit listed on its own, best W of them
        for (auto [val, u] : goods) for (int i = 0; i < u; i++) unitValues.push_back(val);
        sort(unitValues.rbegin(), unitValues.rend());
        long long want = 0;
        for (int i = 0; i < W && i < (int)unitValues.size(); i++) want += unitValues[i];
        if (want != bestUnits(goods, W)) return 1;
    }
}
