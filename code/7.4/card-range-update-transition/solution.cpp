#include <bits/stdc++.h>
using namespace std;

// method: the card's states f[j] (the last 1 at position j) with the range additions done naively; atLeastOne is the reward rule.
long long method(int n, const vector<array<int, 3>>& iv) {
    vector<long long> f(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        f[i] = *max_element(f.begin(), f.begin() + i);
        for (auto [l, r, a] : iv)
            if (r == i)
                for (int j = l; j <= i; j++) f[j] += a;
    }
    return *max_element(f.begin(), f.end());
}
// brute: all strings; an interval pays when the number of ones inside it satisfies the rule (at least one, or exactly one).
long long bruteStrings(int n, const vector<array<int, 3>>& iv, bool exactlyOne) {
    long long best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long total = 0;
        for (auto [l, r, a] : iv) {
            int ones = __builtin_popcount(mask >> (l - 1) & ((1 << (r - l + 1)) - 1));
            if (exactlyOne ? ones == 1 : ones >= 1) total += a;
        }
        best = max(best, total);
    }
    return best;
}
// The second positive example: split into exactly k parts, the value of a part is its number of different values (n small).
long long splitBrute(const vector<int>& a, int k) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {  // bit i set: a cut after position i + 1
        if (__builtin_popcount(mask) != k - 1) continue;
        long long total = 0;
        set<int> part;
        for (int i = 0; i < n; i++) {
            part.insert(a[i]);
            if (i == n - 1 || (mask >> i & 1)) total += part.size(), part.clear();
        }
        best = max(best, total);
    }
    return best;
}
long long splitMethod(const vector<int>& a, int k) {
    int n = a.size();
    vector<long long> prev(n + 1, -1e15), cur;
    prev[0] = 0;
    for (int c = 1; c <= k; c++) {
        vector<long long> f = prev;
        map<int, int> last;
        cur.assign(n + 1, -1e15);
        for (int i = 1; i <= n; i++) {
            for (int j = last[a[i - 1]]; j <= i - 1; j++) f[j] += 1;
            last[a[i - 1]] = i;
            cur[i] = *max_element(f.begin(), f.begin() + i);
        }
        prev = cur;
    }
    return prev[n];
}
int main() {
    vector<array<int, 3>> iv1 = {{1, 2, 10}, {2, 3, -5}, {3, 3, 20}}, iv2 = {{2, 2, 9}, {1, 2, 4}, {1, 1, 2}};
    cout << "P1 brute=" << bruteStrings(3, iv1, false) << " method=" << method(3, iv1) << "\n";
    vector<int> a = {1, 2, 1, 3, 3, 2};
    cout << "P2 brute=" << splitBrute(a, 2) << " method=" << splitMethod(a, 2) << "\n";
    cout << "N1 brute=" << bruteStrings(2, iv2, true) << " method=" << method(2, iv2) << "\n";
}
