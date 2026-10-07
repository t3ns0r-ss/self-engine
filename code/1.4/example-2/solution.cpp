/*
Problem: CSES 1085 Array Division. Divide n positive integers into k consecutive parts so that the
largest part sum is as small as possible; print that sum.
Input: n k (1 <= k <= n <= 2*10^5), then x_1 .. x_n (1 <= x_i <= 10^9).
Output: the smallest possible largest part sum.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    for (auto& v : x) cin >> v;
    // ok(s): fill parts greedily with sums <= s; the fewest parts is at most k (Lemma 1.4.4)
    auto ok = [&](long long s) {
        int parts = 1;
        long long cur = 0;
        for (long long v : x) {
            if (v > s) return false;  // this element fits in no part
            if (cur + v > s) {
                parts++;
                cur = 0;
            }
            cur += v;
        }
        return parts <= k;
    };
    long long lo = 0, hi = 0;  // ok(0) is false (values are positive); ok(total) is true
    for (long long v : x) hi += v;  // total up to 2*10^14
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";
}
