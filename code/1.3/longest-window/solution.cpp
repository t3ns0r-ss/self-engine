/*
Problem: longest contiguous segment with sum at most K.
Input: n K, then n positive integers a[0..n-1].
Output: the maximum length (0 if no single element fits).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.1. The length of the longest window with sum at most K (non-negative values).
int longestWindow(const vector<long long>& a, long long K) {
    long long sum = 0;  // sum of a[l..r]
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > K) {  // window [l, r] invalid: shrink from the left
            sum -= a[l];
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    long long K;  // K and sums can reach 2*10^14, beyond int
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << longestWindow(a, K) << "\n";
}
