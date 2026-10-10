#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.1. L[i] = 1 + the largest L[j] over earlier positions j with a[j] < a[i]; the LIS length is the maximum.
vector<int> endingAt(const vector<int>& a) {
    int n = a.size();
    vector<int> L(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) L[i] = max(L[i], L[j] + 1);
    return L;
}
// snippet:end

int brute(const vector<int>& a) {
    int best = 0, n = a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        int last = INT_MIN, len = 0;
        bool ok = true;
        for (int i = 0; i < n && ok; i++) if (mask >> i & 1) { if (a[i] <= last) ok = false; last = a[i], len++; }
        if (ok) best = max(best, len);
    }
    return best;
}
int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    auto L = endingAt(a);
    cout << "L for 3 1 4 1 5 9 2 6:";
    for (int x : L) cout << ' ' << x;
    cout << ", the LIS length is " << *max_element(L.begin(), L.end()) << '\n';
    mt19937 rng(31);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 11;
        vector<int> b(n);
        for (int& x : b) x = rng() % 8;
        auto l = endingAt(b);
        if (*max_element(l.begin(), l.end()) != brute(b)) return 1;
    }
}
