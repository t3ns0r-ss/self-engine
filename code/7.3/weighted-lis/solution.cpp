#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers a_i with weights w_i (a weight may be negative). Print the largest total weight of a non-empty subsequence in
which the values a_i strictly increase.
Input: n, then the n values a_i, then the n weights w_i.
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
// Theorem 7.3.1: dp = w[i] + max(0, max dp[j] over j < i with a[j] < a[i]), by a Fenwick tree of prefix maxima over the ranks.
long long heaviestIncreasing(const vector<int>& a, const vector<long long>& w) {
    vector<int> rank;
    int m = compress(a, rank);
    FenwickMax tree(m);
    long long best = LLONG_MIN;
    for (size_t i = 0; i < a.size(); i++) {
        long long dp = w[i] + tree.query(rank[i] - 1);  // asked before the insertion: equal values do not see each other
        tree.update(rank[i], dp);
        best = max(best, dp);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> w(n);
    for (int& x : a) cin >> x;
    for (long long& x : w) cin >> x;
    cout << heaviestIncreasing(a, w) << "\n";
}
