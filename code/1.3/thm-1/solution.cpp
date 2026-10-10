#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.1. The length of the longest window with sum at most K (non-negative values):
// for each right end r, move l right while the window is invalid.
int longestWindow(const vector<long long>& a, long long K) {
    long long sum = 0;  // sum of a[l..r]
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > K) {  // window [l, r] invalid: shrink from the left
            sum -= a[l];
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
// snippet:end

int main() {
    cout << "3 1 2 1 4 1, sum at most 5: longest window " << longestWindow({3, 1, 2, 1, 4, 1}, 5) << '\n';
    cout << "5 5, sum at most 4: longest window " << longestWindow({5, 5}, 4) << '\n';
    cout << "1 1 1, sum at most 3: longest window " << longestWindow({1, 1, 1}, 3) << '\n';
    mt19937 rng(1);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8 + 1;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 5;
        long long K = rng() % 9;
        int best = 0;
        for (int l = 0; l < n; l++) for (int r = l, s = 0; r < n; r++) { s += a[r]; if (s <= K) best = max(best, r - l + 1); }
        if (best != longestWindow(a, K)) return 1;
    }
}
