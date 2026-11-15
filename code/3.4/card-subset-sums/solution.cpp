#include <bits/stdc++.h>
using namespace std;

int reachableCount(const vector<int>& a) {
    bitset<64> reach;
    reach[0] = 1;
    for (int x : a) reach |= reach << x;
    return reach.count();
}
int main() {
    // P1: the number of different sums of subsets of 2 3 7. Brute: all 8 subsets. Method: the bitset.
    vector<int> a = {2, 3, 7};
    set<int> sums;
    for (int mask = 0; mask < 8; mask++) {
        int s = 0;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) s += a[i];
        sums.insert(s);
    }
    cout << "P1 brute=" << sums.size() << " method=" << reachableCount(a) << '\n';
    // N1: the subset sum closest to T among 36 numbers near 10^9; the reachable sums go up to 3.6 * 10^10.
    mt19937_64 rng(77);
    vector<long long> v(36);
    long long total = 0;
    for (auto& x : v) x = 900000000 + rng() % 100000000, total += x;
    long long T = total / 2;
    auto sums2 = [&](int from, int to) {
        vector<long long> s = {0};
        for (int i = from; i < to; i++) { int sz = s.size(); for (int j = 0; j < sz; j++) s.push_back(s[j] + v[i]); }
        return s;
    };
    auto L = sums2(0, 18), R = sums2(18, 36);
    sort(R.begin(), R.end());
    long long best = 0;
    for (long long x : L) if (x <= T) best = max(best, x + *prev(upper_bound(R.begin(), R.end(), T - x)));
    cout << "N1 brute=" << best << " method=" << (total > 100000000LL ? "too-slow" : "ok") << '\n';
}
