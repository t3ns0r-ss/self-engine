/*
Problem: count the pairs of positions i < j with a[i] + a[j] <= T.
Input: n T, then n integers a[0..n-1] (any order, may be negative).
Output: the number of pairs.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.4, counting form. The number of pairs i < j with a_i + a_j <= T.
long long pairsAtMost(vector<long long> a, long long T) {
    sort(a.begin(), a.end());
    long long pairs = 0;
    int l = 0, r = a.size() - 1;
    while (l < r) {
        if (a[l] + a[r] <= T) {
            pairs += r - l;  // a[l] pairs with every index in (l, r]
            l++;
        } else {
            r--;  // a[r] pairs with no index left in [l, r)
        }
    }
    return pairs;
}
// snippet:end

int main() {
    int n;
    long long T;  // sums of two values reach 2*10^9, beyond int
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << pairsAtMost(a, T) << "\n";
}
