/*
Problem: do two different positions i < j exist with a[i] + a[j] = T?
Input: n T, then n integers a[0..n-1] (any order, may be negative).
Output: YES or NO.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;  // sums of two values up to 10^9 in size reach 2*10^9, beyond int
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    bool found = false;
    while (l < r) {
        long long s = a[l] + a[r];
        if (s == T) {
            found = true;
            break;
        }
        if (s < T) l++;  // a[l] is too small even with the largest partner left
        else r--;        // a[r] is too large even with the smallest partner left
    }
    cout << (found ? "YES" : "NO") << "\n";
}
