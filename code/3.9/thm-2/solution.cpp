#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.9.2. The 2^k subset sums of k numbers, built from the sums of the first i - 1 numbers: each step adds one
// number to every sum already listed, so the whole list costs 2^k - 1 additions (not k * 2^(k-1)).
vector<long long> subsetSums(const vector<long long>& v, long long& additions) {
    vector<long long> sums = {0};
    for (long long x : v) {
        int size = sums.size();
        for (int j = 0; j < size; j++) { sums.push_back(sums[j] + x); additions++; }
    }
    return sums;
}
// snippet:end

// the same list, recomputing every mask from its bits: one addition per set bit
vector<long long> subsetSumsByMask(const vector<long long>& v, long long& additions) {
    int k = v.size();
    vector<long long> sums(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++)
        for (int i = 0; i < k; i++)
            if (mask >> i & 1) { sums[mask] += v[i]; additions++; }
    return sums;
}

int main() {
    vector<long long> v = {3, 5, 2, 6};
    long long fast = 0, slow = 0;
    vector<long long> a = subsetSums(v, fast), b = subsetSumsByMask(v, slow);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    cout << "4 numbers, additions: building on the previous list " << fast << ", from the bits of every mask " << slow << '\n';
    cout << "same sums: " << (a == b ? "yes" : "no") << '\n';
    fast = slow = 0;
    vector<long long> w(20, 1);
    subsetSums(w, fast);
    subsetSumsByMask(w, slow);
    cout << "20 numbers, additions: " << fast << " against " << slow << '\n';
    if (fast != (1 << 20) - 1) return 1;
}
