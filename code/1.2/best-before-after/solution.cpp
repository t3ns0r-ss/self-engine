/*
Problem: for n integers, print (1) the largest sum of a non-empty subarray, and (2) for every i, the
largest element other than a_i.
Input: n (2 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the largest subarray sum; line 2: n values.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // (1) best P_j - min(P_0..P_{j-1}) over j = 1..n (Theorem 1.2.5, part 4)
    long long P = 0, minP = 0, best = LLONG_MIN;  // minP starts as P_0 = 0
    for (int j = 0; j < n; j++) {
        P += a[j];                    // now P = P_{j+1}
        best = max(best, P - minP);   // subarray ending at j, best start
        minP = min(minP, P);          // P_{j+1} becomes available for later ends
    }
    cout << best << "\n";

    // (2) max(prefix before i, suffix after i) (part 2); LLONG_MIN stands for an empty side
    vector<long long> pre(n + 1, LLONG_MIN), suf(n + 1, LLONG_MIN);
    for (int i = 0; i < n; i++) pre[i + 1] = max(pre[i], a[i]);          // pre[k] = max of a[0..k-1]
    for (int i = n - 1; i >= 0; i--) suf[i] = max(suf[i + 1], a[i]);     // suf[k] = max of a[k..n-1]
    for (int i = 0; i < n; i++) cout << max(pre[i], suf[i + 1]) << (i + 1 < n ? ' ' : '\n');
}
