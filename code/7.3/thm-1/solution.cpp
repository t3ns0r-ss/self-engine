#include <bits/stdc++.h>
using namespace std;

// Ranks 1..m of the values: equal values get equal ranks. Outside the snippet (sorting and unique, topic 1.1).
int compress(const vector<int>& a, vector<int>& rank) {
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    rank.resize(a.size());
    for (size_t i = 0; i < a.size(); i++) rank[i] = lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin() + 1;
    return sorted.size();
}

// snippet:begin
// Theorem 7.3.1. A Fenwick tree for prefix maxima: update(r, v) raises the value stored at rank r, query(r) is the maximum
// over the ranks 1..r (0 if nothing is stored, which also means "start a new subsequence here").
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
// dp[i] = w[i] + max(0, max dp[j] over j < i with a[j] < a[i]): the heaviest increasing subsequence that ends at i.
vector<long long> heaviestIncreasing(const vector<int>& rank, int m, const vector<long long>& w) {
    FenwickMax tree(m);
    vector<long long> dp(rank.size());
    for (size_t i = 0; i < rank.size(); i++) {
        dp[i] = w[i] + tree.query(rank[i] - 1);  // smaller ranks only, asked before i is inserted
        tree.update(rank[i], dp[i]);
    }
    return dp;
}
// snippet:end

vector<long long> bruteDp(const vector<int>& a, const vector<long long>& w) {
    vector<long long> dp(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        long long best = 0;
        for (size_t j = 0; j < i; j++)
            if (a[j] < a[i]) best = max(best, dp[j]);
        dp[i] = w[i] + best;
    }
    return dp;
}

int main() {
    vector<int> a = {3, 1, 4, 1, 5}, rank;
    vector<long long> w = {2, 3, 1, 4, 5};
    int m = compress(a, rank);
    auto dp = heaviestIncreasing(rank, m, w);
    cout << "dp:";
    for (long long x : dp) cout << " " << x;
    cout << "\nheaviest: " << *max_element(dp.begin(), dp.end()) << "\n";
    vector<int> b = {2, 2}, rankB;
    int mB = compress(b, rankB);
    auto dpB = heaviestIncreasing(rankB, mB, {5, 5});
    cout << "equal keys, strict: " << dpB[0] << " " << dpB[1] << "\n";
    // Check (not printed): 3000 random arrays of up to 9 numbers, weights from -5 to 10, against the O(n^2) definition.
    mt19937 rng(11);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 9 + 1;
        vector<int> x(n), rk;
        vector<long long> y(n);
        for (int i = 0; i < n; i++) x[i] = rng() % 5 + 1, y[i] = (long long)(rng() % 16) - 5;
        int mm = compress(x, rk);
        if (heaviestIncreasing(rk, mm, y) != bruteDp(x, y)) return 1;
    }
}
