#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.3. A total over configurations is a sum over elements of value times the number of configurations in which
// it counts: subarray sums (a[i] lies in (i+1)(n-i) subarrays) and subset maxima (a[i] is the maximum of 2^i subsets).
long long sumOfSubarraySums(const vector<long long>& a) {
    long long n = a.size(), total = 0;
    for (long long i = 0; i < n; i++) total += a[i] * (i + 1) * (n - i);
    return total;
}
long long sumOfSubsetMaxima(vector<long long> a) {  // distinct values
    sort(a.begin(), a.end());
    long long total = 0;
    for (size_t i = 0; i < a.size(); i++) total += a[i] << i;
    return total;
}
// snippet:end

int main() {
    cout << "sum of the sums of all subarrays of 1 2 3: " << sumOfSubarraySums({1, 2, 3}) << '\n';
    cout << "sum of the maxima of all non-empty subsets of 1 2 3: " << sumOfSubsetMaxima({1, 2, 3}) << '\n';
    mt19937 rng(5);
    for (int round = 0; round < 200; round++) {
        int n = 1 + rng() % 8;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 20;
        long long sub = 0;
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) for (int i = l; i <= r; i++) sub += a[i];
        if (sub != sumOfSubarraySums(a)) return 1;
        set<long long> s(a.begin(), a.end());
        vector<long long> d(s.begin(), s.end());
        long long mx = 0;
        for (int mask = 1; mask < (1 << d.size()); mask++) {
            long long best = 0;
            for (size_t i = 0; i < d.size(); i++) if (mask >> i & 1) best = max(best, d[i]);
            mx += best;
        }
        if (mx != sumOfSubsetMaxima(d)) return 1;
    }
}
