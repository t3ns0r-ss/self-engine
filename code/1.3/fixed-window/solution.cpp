/*
Problem: the largest number of distinct values in any segment of length exactly k.
Input: n k (1 <= k <= n), then n integers a[0..n-1].
Output: that number.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    map<int, int> cnt;  // value -> occurrences in the current window
    int best = 0;
    for (int r = 0; r < n; r++) {
        cnt[a[r]]++;                     // a[r] enters
        if (r >= k) {                    // a[r - k] leaves
            if (--cnt[a[r - k]] == 0) cnt.erase(a[r - k]);
        }
        if (r >= k - 1) best = max(best, (int)cnt.size());  // window is a[r-k+1..r]
    }
    cout << best << "\n";
}
