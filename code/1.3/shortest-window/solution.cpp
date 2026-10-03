/*
Problem: shortest contiguous segment with sum at least S.
Input: n S (S >= 1), then n positive integers a[0..n-1].
Output: the minimum length, or 0 if no segment reaches S.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long S;  // S and sums can reach 2*10^14, beyond int
    cin >> n >> S;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    long long sum = 0;  // sum of a[l..r]
    int l = 0, best = n + 1;  // n + 1 means "none found yet"
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= S) {  // [l, r] reaches S: record it, then try a shorter one
            best = min(best, r - l + 1);
            sum -= a[l];
            l++;
        }
    }
    cout << (best == n + 1 ? 0 : best) << "\n";
}
