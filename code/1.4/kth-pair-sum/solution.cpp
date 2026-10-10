/*
Problem: arrays A (n values) and B (m values); among all n * m sums A_i + B_j, print the k-th smallest.
Input: n m k (1 <= n, m <= 10^5, 1 <= k <= n * m), then A, then B (|values| <= 10^9).
Output: the k-th smallest sum.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.6. The k-th smallest of all sums A_i + B_j: the smallest x such that at least k pair sums are <= x.
long long kthPairSum(const vector<long long>& A, vector<long long> B, long long k) {
    sort(B.begin(), B.end());
    // count(x) = number of pairs with A_i + B_j <= x: for each i, the B_j <= x - A_i
    auto count = [&](long long x) {
        long long c = 0;
        for (long long a : A) c += upper_bound(B.begin(), B.end(), x - a) - B.begin();
        return c;
    };
    long long lo = -2000000001, hi = 2000000000;  // count(lo) = 0 < k, count(hi) = n * m >= k
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (count(mid) >= k) hi = mid;
        else lo = mid;
    }
    return hi;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;  // up to 10^10
    cin >> n >> m >> k;
    vector<long long> A(n), B(m);
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;
    cout << kthPairSum(A, B, k) << "\n";
}
