/*
Problem: count the subsets (including the empty one) of n values whose sum lies in [L, R].
Input: n L R, then a_0 .. a_{n-1} (1 <= n <= 20, 0 <= a_i <= 10^9, 0 <= L <= R <= 2*10^10).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.2. The number of subsets (the empty one included) whose sum lies in [lo, hi], one bitmask per subset.
int countSubsets(const vector<long long>& a, long long lo, long long hi) {
    int n = a.size(), count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {  // every subset once
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) sum += a[i];  // item i is in the subset
        if (lo <= sum && sum <= hi) count++;
    }
    return count;
}
// snippet:end

int main() {
    int n;
    long long lo, hi;
    cin >> n >> lo >> hi;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << countSubsets(a, lo, hi) << "\n";
}
