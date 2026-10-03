/*
Problem: count the pairs of positions i < j with a[i] + a[j] <= T.
Input: n T, then n integers a[0..n-1] (any order, may be negative).
Output: the number of pairs.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;  // sums of two values reach 2*10^9, beyond int
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    long long pairs = 0;  // up to n(n-1)/2, beyond int for large n
    int l = 0, r = n - 1;
    while (l < r) {
        if (a[l] + a[r] <= T) {
            pairs += r - l;  // a[l] pairs with every index in (l, r]
            l++;
        } else {
            r--;  // a[r] pairs with no index left in [l, r)
        }
    }
    cout << pairs << "\n";
}
