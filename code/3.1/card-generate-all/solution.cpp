#include <bits/stdc++.h>
using namespace std;

long long distinctSubsets(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size();
    long long found = 0;
    function<void(int)> rec = [&](int start) {
        found++;
        for (int i = start; i < n; i++) {
            if (i > start && a[i] == a[i - 1]) continue;
            rec(i + 1);
        }
    };
    rec(0);
    return found;
}
long long distinctPermutations(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size(), depth = 0;
    vector<bool> used(n, false);
    long long found = 0;
    function<void()> rec = [&]() {
        if (depth == n) { found++; return; }
        for (int i = 0; i < n; i++) {
            if (used[i] || (i > 0 && a[i] == a[i - 1] && !used[i - 1])) continue;
            used[i] = true, depth++;
            rec();
            depth--, used[i] = false;
        }
    };
    rec();
    return found;
}
int main() {
    // P1: the distinct sub-multisets of 1 2 2. Brute: every bitmask, as a sorted vector in a set. Method: the skip rule.
    vector<int> a = {1, 2, 2};
    set<vector<int>> s;
    for (int mask = 0; mask < 8; mask++) {
        vector<int> v;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) v.push_back(a[i]);
        s.insert(v);
    }
    cout << "P1 brute=" << s.size() << " method=" << distinctSubsets(a) << '\n';
    // P2: the distinct arrangements of A A B. Brute: next_permutation. Method: left-to-right placement of equal values.
    vector<int> b = {1, 1, 2};
    long long brute = 0;
    do brute++; while (next_permutation(b.begin(), b.end()));
    cout << "P2 brute=" << brute << " method=" << distinctPermutations({1, 1, 2}) << '\n';
    // N1: the arrangements of 20 letters A and 20 letters B. The count is C(40, 20); listing them visits that many leaves.
    long long c = 1;
    for (int i = 1; i <= 20; i++) c = c * (20 + i) / i;
    cout << "N1 brute=" << c << " method=" << (c > 1000000000LL ? "too-slow" : "ok") << '\n';
    // N2: the ways to climb 40 stairs with steps of 1 or 2. The recursion f(n) = f(n-1) + f(n-2) makes about 2 f(n) calls.
    vector<long long> f(41, 1);
    for (int i = 2; i <= 40; i++) f[i] = f[i - 1] + f[i - 2];
    cout << "N2 brute=" << f[40] << " method=" << (2 * f[40] > 100000000LL ? "too-slow" : "ok") << '\n';
}
