#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers a_i. For every distinct non-empty non-decreasing sequence of values that appears as a subsequence, take the
product of its values; print the sum of these products modulo 10^9 + 7. (Equal sequences from different index sets count once.)
Input: n, then the n numbers.
Output: the sum.
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
// Theorem 7.3.3: prefix sums modulo MOD over ranks.
const long long MOD = 1'000'000'007;
struct FenwickSum {
    vector<long long> t;
    FenwickSum(int n) : t(n + 1, 0) {}
    void add(int r, long long v) {
        for (; r < (int)t.size(); r += r & -r) t[r] = (t[r] + v + MOD) % MOD;
    }
    long long prefix(int r) {
        long long s = 0;
        for (; r > 0; r -= r & -r) s += t[r];
        return s % MOD;
    }
};

// snippet:begin
// Theorem 7.3.3 with a replacement: f[v] = sum of the products of the distinct sequences that end with the value v. For a[i] the new
// f is a[i] * (1 + sum of f over values <= a[i]); it contains the old f[a[i]], so it replaces it.
long long sumOfProducts(const vector<int>& a) {
    vector<int> rank;
    int m = compress(a, rank);
    FenwickSum tree(m);
    vector<long long> f(m + 1, 0);
    for (size_t i = 0; i < a.size(); i++) {
        long long now = a[i] % MOD * (1 + tree.prefix(rank[i])) % MOD;
        tree.add(rank[i], now - f[rank[i]]);
        f[rank[i]] = now;
    }
    return tree.prefix(m);
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << sumOfProducts(a) << "\n";
}
