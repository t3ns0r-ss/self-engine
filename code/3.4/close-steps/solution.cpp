/*
Problem: the longest subsequence of an array in which every two consecutive chosen elements differ by at most k.
Input: n k (1 <= n <= 5000, 0 <= k <= 10^9), then n integers (|a_i| <= 10^9).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // L[i] = longest valid subsequence ending at position i (Theorem 3.4.1 with the rule |a_j - a_i| <= k)
    vector<int> L(n, 1);
    int best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (llabs(a[i] - a[j]) <= k) L[i] = max(L[i], L[j] + 1);  // a_i may follow a_j
        best = max(best, L[i]);
    }
    cout << best << "\n";
}
