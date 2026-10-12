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
// Theorem 7.3.3. cnt[i] = 1 + sum of cnt[j] over j < i with a[j] < a[i], modulo MOD: a Fenwick tree of sums over the ranks.
const long long MOD = 1'000'000'007;
struct FenwickSum {
    vector<long long> t;
    FenwickSum(int n) : t(n + 1, 0) {}
    void add(int r, long long v) {  // v may be negative (|v| < MOD)
        for (; r < (int)t.size(); r += r & -r) t[r] = (t[r] + v + MOD) % MOD;
    }
    long long prefix(int r) {
        long long s = 0;
        for (; r > 0; r -= r & -r) s += t[r];
        return s % MOD;
    }
};
// The number of non-empty strictly increasing subsequences. With distinct = true a sequence of values is counted once: the
// value stored for a rank is replaced by the new count (it contains the old one), not added to.
long long countIncreasing(const vector<int>& rank, int m, bool distinct) {
    FenwickSum tree(m);
    vector<long long> stored(m + 1, 0);
    for (int r : rank) {
        long long cnt = (1 + tree.prefix(r - 1)) % MOD;
        tree.add(r, distinct ? cnt - stored[r] : cnt);
        stored[r] = cnt;
    }
    return tree.prefix(m);
}
// snippet:end

long long bruteCount(const vector<int>& a, bool distinct) {
    int n = a.size();
    set<vector<int>> seen;
    long long count = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<int> seq;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) seq.push_back(a[i]);
        bool ok = true;
        for (size_t i = 1; i < seq.size(); i++) ok &= seq[i - 1] < seq[i];
        if (!ok) continue;
        if (distinct) count += seen.insert(seq).second;
        else count++;
    }
    return count;
}

int main() {
    auto run = [](vector<int> a, bool distinct) {
        vector<int> rank;
        int m = compress(a, rank);
        return countIncreasing(rank, m, distinct);
    };
    cout << "by positions, 3 1 2 4: " << run({3, 1, 2, 4}, false) << "\n";
    cout << "by positions, 1 1 2: " << run({1, 1, 2}, false) << "\n";
    cout << "distinct, 1 1 2: " << run({1, 1, 2}, true) << "\n";
    // Check (not printed): 3000 random arrays of up to 10 numbers, both modes, against the enumeration of all subsequences.
    mt19937 rng(13);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 10 + 1;
        vector<int> a(n);
        for (auto& x : a) x = rng() % 5 + 1;
        if (run(a, false) != bruteCount(a, false) || run(a, true) != bruteCount(a, true)) return 1;
    }
}
