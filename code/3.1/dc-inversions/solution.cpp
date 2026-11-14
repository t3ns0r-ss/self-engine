/*
Problem: count the inversions of an array (pairs i < j with a[i] > a[j]).
Input: n (0 <= n <= 2 * 10^5), then n integers (-10^9 <= a_i <= 10^9).
Output: the number of inversions.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Divide and conquer (Theorem 3.1.5): count inside the left half, inside the right half, and across the middle
// while merging. Equal values are not inversions, so on a tie the left value goes first.
long long countInversions(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    long long cnt = countInversions(a, tmp, l, m) + countInversions(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) {
            tmp[k++] = a[i++];
        } else {
            cnt += m - i;
            tmp[k++] = a[j++];
        }
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return cnt;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n), tmp(n);
    for (int& x : a) cin >> x;
    cout << countInversions(a, tmp, 0, n) << "\n";
}
