/*
Problem: maximum sum of a non-empty contiguous subarray (the idea of LeetCode 53, solved by divide and conquer).
Input: n (1 <= n <= 2 * 10^5), then n integers (|a_i| <= 10^4).
Output: the largest sum of a non-empty subarray.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Divide and conquer: the best subarray of a[l..r-1] lies in the left half, in the right half, or crosses the middle.
// A crossing one is the best suffix of the left half plus the best prefix of the right half, and both must be non-empty.
long long maxSubarray(const vector<int>& a, int l, int r) {
    if (r - l == 1) return a[l];
    int m = (l + r) / 2;
    long long best = max(maxSubarray(a, l, m), maxSubarray(a, m, r));
    long long sum = 0, bestLeft = LLONG_MIN, bestRight = LLONG_MIN;
    for (int i = m - 1; i >= l; i--) {
        sum += a[i];
        bestLeft = max(bestLeft, sum);  // best sum of a[i..m-1]
    }
    sum = 0;
    for (int j = m; j < r; j++) {
        sum += a[j];
        bestRight = max(bestRight, sum);  // best sum of a[m..j]
    }
    return max(best, bestLeft + bestRight);
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << maxSubarray(a, 0, n) << "\n";
}
