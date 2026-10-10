/*
Problem: do two different positions i < j exist with a[i] + a[j] = T?
Input: n T, then n integers a[0..n-1] (any order, may be negative).
Output: YES or NO.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.4. Is there a pair i < j with a_i + a_j = T? Sort, then move the pointers inwards.
bool pairWithSum(vector<long long> a, long long T) {
    sort(a.begin(), a.end());
    int l = 0, r = a.size() - 1;
    while (l < r) {
        long long s = a[l] + a[r];
        if (s == T) return true;
        if (s < T) l++;  // a[l] is too small even with the largest partner left
        else r--;        // a[r] is too large even with the smallest partner left
    }
    return false;
}
// snippet:end

int main() {
    int n;
    long long T;  // sums of two values up to 10^9 in size reach 2*10^9, beyond int
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << (pairWithSum(a, T) ? "YES" : "NO") << "\n";
}
