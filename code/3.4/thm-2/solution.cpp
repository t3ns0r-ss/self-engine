#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.2. The tails array: tails[k] = the smallest last value of an increasing subsequence of length k + 1. A new
// element replaces the first tail >= x, or extends the array.
vector<int> tailsAfter(const vector<int>& a, vector<vector<int>>* trace = nullptr) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
        if (trace) trace->push_back(tails);
    }
    return tails;
}
// snippet:end

int main() {
    vector<vector<int>> trace;
    auto tails = tailsAfter({3, 1, 4, 1, 5, 9, 2, 6}, &trace);
    for (auto& t : trace) {
        cout << "tails:";
        for (int x : t) cout << ' ' << x;
        cout << '\n';
    }
    cout << "LIS length " << tails.size() << '\n';
    mt19937 rng(32);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 11;
        vector<int> b(n);
        for (int& x : b) x = rng() % 8;
        int best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int last = INT_MIN, len = 0;
            bool ok = true;
            for (int i = 0; i < n && ok; i++) if (mask >> i & 1) { if (b[i] <= last) ok = false; last = b[i], len++; }
            if (ok) best = max(best, len);
        }
        if ((int)tailsAfter(b).size() != best) return 1;
    }
}
