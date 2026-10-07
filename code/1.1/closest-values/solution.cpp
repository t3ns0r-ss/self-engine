/*
Problem: for n integers and k, print the smallest difference between two of the values, and the
smallest possible (largest - smallest) over all choices of k of the values.
Input: n k (2 <= n <= 2*10^5, 1 <= k <= n), then a_1 .. a_n (|a_i| <= 10^9).
Output: "minDifference minSpread".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);  // differences reach 2*10^9, beyond int
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());  // the question is order-free (Theorem 1.1.2)
    long long minDiff = LLONG_MAX, minSpread = LLONG_MAX;
    for (int i = 0; i + 1 < n; i++) minDiff = min(minDiff, a[i + 1] - a[i]);  // neighbours only
    for (int i = 0; i + k - 1 < n; i++) minSpread = min(minSpread, a[i + k - 1] - a[i]);  // blocks of k
    cout << minDiff << " " << minSpread << "\n";
}
