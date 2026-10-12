#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers a_i with weights w_i. Choose a subsequence in which the values strictly increase and any two consecutive chosen
indices differ by at least k. Print the largest total weight of a non-empty choice.
Input: n and k, then the n values a_i, then the n weights w_i.
Output: the largest total weight.
*/

// Ranks 1..m of the values; equal values have equal ranks (sorting and unique, topic 1.1).
int compress(const vector<int>& a, vector<int>& rank) {
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    rank.resize(a.size());
    for (size_t i = 0; i < a.size(); i++) rank[i] = lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin() + 1;
    return sorted.size();
}
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
// Theorem 7.3.1 with the distance rule: when i is processed, the indices up to i - k are in the tree and no later ones.
long long heaviestWithGap(const vector<int>& a, const vector<long long>& w, int k) {
    vector<int> rank;
    int m = compress(a, rank);
    FenwickMax tree(m);
    vector<long long> dp(a.size());
    long long best = LLONG_MIN;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i - k >= 0) tree.update(rank[i - k], dp[i - k]);  // the index i - k is allowed from now on
        dp[i] = w[i] + tree.query(rank[i] - 1);
        best = max(best, dp[i]);
    }
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<long long> w(n);
    for (int& x : a) cin >> x;
    for (long long& x : w) cin >> x;
    cout << heaviestWithGap(a, w, k) << "\n";
}
