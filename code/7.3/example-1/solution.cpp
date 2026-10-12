#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder Educational DP Contest, task Q, Flowers. N flowers stand in a row; flower i has a height h_i (all heights are
different, a permutation of 1..N) and a beauty a_i. Remove some flowers so that the heights of the remaining ones increase from left
to right. Print the largest possible sum of the beauties of the remaining flowers. (N up to 2·10^5, a_i up to 10^9.)
Input: N, then the heights, then the beauties.
*/

// Theorem 7.3.1: prefix maxima over ranks (0 when nothing is stored).
struct FenwickMax {
    vector<long long> t;
    FenwickMax(int n) : t(n + 1, 0) {}
    void update(int r, long long v) {
        for (; r < (int)t.size(); r += r & -r) t[r] = max(t[r], v);
    }
    long long query(int r) {
        long long best = 0;
        for (; r > 0; r -= r & -r) best = max(best, t[r]);
        return best;
    }
};

// snippet:begin
// Theorem 7.3.1: dp = a[i] + max dp[j] over j < i with h[j] < h[i]. The heights are 1..N, so they are their own ranks.
long long mostBeautiful(const vector<int>& h, const vector<long long>& a) {
    FenwickMax tree(h.size());
    long long best = 0;
    for (size_t i = 0; i < h.size(); i++) {
        long long dp = a[i] + tree.query(h[i] - 1);
        tree.update(h[i], dp);
        best = max(best, dp);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    vector<long long> a(n);
    for (int& x : h) cin >> x;
    for (long long& x : a) cin >> x;
    cout << mostBeautiful(h, a) << "\n";
}
