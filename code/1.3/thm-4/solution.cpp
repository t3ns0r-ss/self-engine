#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.4. In a sorted array: positions of a pair with sum T (or {-1, -1}), and the number of pairs with sum at most T.
pair<int, int> findPair(const vector<long long>& a, long long T) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        long long s = a[l] + a[r];
        if (s == T) return {l, r};
        if (s < T) l++;  // a[l] is too small even with the largest partner left
        else r--;        // a[r] is too large even with the smallest partner left
    }
    return {-1, -1};
}

long long pairsAtMost(const vector<long long>& a, long long T) {
    long long pairs = 0;
    int l = 0, r = a.size() - 1;
    while (l < r) {
        if (a[l] + a[r] <= T) pairs += r - l, l++;  // a[l] pairs with every index in (l, r]
        else r--;
    }
    return pairs;
}
// snippet:end

int main() {
    vector<long long> a = {1, 2, 4, 6, 9};
    pair<int, int> p = findPair(a, 8);
    cout << "1 2 4 6 9, target 8: positions " << p.first << " " << p.second << '\n';
    cout << "1 2 4 6 9, target 100: " << (findPair(a, 100).first < 0 ? "none" : "found") << '\n';
    cout << "1 2 4 6 9: pairs with sum at most 8: " << pairsAtMost(a, 8) << '\n';
    mt19937 rng(4);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 7 + 1;
        vector<long long> b(n);
        for (auto& x : b) x = rng() % 12;
        sort(b.begin(), b.end());
        long long T = rng() % 20, count = 0;
        bool any = false;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) any |= b[i] + b[j] == T, count += b[i] + b[j] <= T;
        if (any != (findPair(b, T).first >= 0) || count != pairsAtMost(b, T)) return 1;
    }
}
