/*
Problem: longest contiguous segment with sum at most K.
Input: n K, then n positive integers a[0..n-1].
Output: the maximum length (0 if no single element fits).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;  // K and sums can reach 2*10^14, beyond int
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    long long sum = 0;  // sum of a[l..r]
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > K) {  // window [l, r] invalid: shrink from the left
            sum -= a[l];
            l++;
        }
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
