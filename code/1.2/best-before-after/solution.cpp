/*
Problem: for n integers, print (1) the largest sum of a non-empty subarray, and (2) for every i, the
largest element other than a_i.
Input: n (2 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: the largest subarray sum; line 2: n values.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.5. The largest subarray sum, and for each i the largest element other than a_i.
long long bestSubarray(const vector<long long>& a) {
    long long P = 0, minP = 0, best = LLONG_MIN;  // minP starts as P_0 = 0
    for (long long x : a) {
        P += x;                       // now P = P_{j+1}
        best = max(best, P - minP);   // subarray ending here, best start
        minP = min(minP, P);          // P_{j+1} becomes available for later ends
    }
    return best;
}

vector<long long> maxWithout(const vector<long long>& a) {
    int n = a.size();
    vector<long long> pre(n + 1, LLONG_MIN), suf(n + 1, LLONG_MIN), res(n);  // LLONG_MIN stands for an empty side
    for (int i = 0; i < n; i++) pre[i + 1] = max(pre[i], a[i]);       // pre[k] = max of a[0..k-1]
    for (int i = n - 1; i >= 0; i--) suf[i] = max(suf[i + 1], a[i]);  // suf[k] = max of a[k..n-1]
    for (int i = 0; i < n; i++) res[i] = max(pre[i], suf[i + 1]);
    return res;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << bestSubarray(a) << "\n";
    vector<long long> r = maxWithout(a);
    for (int i = 0; i < n; i++) cout << r[i] << (i + 1 < n ? ' ' : '\n');
}
