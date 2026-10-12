#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers a_i and a length t. Print the number of subsequences of exactly t elements whose values strictly increase
(subsequences with different index sets are different), modulo 10^9 + 7.
Input: n and t, then the n numbers.
Output: the count.
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
// Theorem 7.3.3, one tree for each length: cnt[len][i] = sum of cnt[len - 1][j] over j < i with a[j] < a[i].
long long countOfLength(const vector<int>& a, int t) {
    vector<int> rank;
    int m = compress(a, rank);
    vector<FenwickSum> layer(t + 1, FenwickSum(m));
    long long total = 0;
    for (int r : rank) {
        for (int len = t; len >= 1; len--) {  // longest first, so that the element is not used twice
            long long cnt = len == 1 ? 1 : layer[len - 1].prefix(r - 1);
            layer[len].add(r, cnt);
            if (len == t) total = (total + cnt) % MOD;
        }
    }
    return total;
}
// snippet:end

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << countOfLength(a, t) << "\n";
}
