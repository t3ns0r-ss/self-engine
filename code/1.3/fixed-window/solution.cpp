/*
Problem: the largest number of distinct values in any segment of length exactly k.
Input: n k (1 <= k <= n), then n integers a[0..n-1].
Output: that number.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.3. The largest number of distinct values in a window of exactly k elements.
int mostDistinct(const vector<int>& a, int k) {
    map<int, int> cnt;  // value -> occurrences in the current window
    int best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        cnt[a[r]]++;     // a[r] enters
        if (r >= k) {    // a[r - k] leaves
            if (--cnt[a[r - k]] == 0) cnt.erase(a[r - k]);
        }
        if (r >= k - 1) best = max(best, (int)cnt.size());  // window is a[r-k+1..r]
    }
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << mostDistinct(a, k) << "\n";
}
