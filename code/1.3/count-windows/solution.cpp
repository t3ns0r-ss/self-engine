/*
Problem: count the contiguous segments containing at most k distinct values.
Input: n k, then n integers a[0..n-1] (any values).
Output: the number of such segments.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.2. The number of non-empty windows with at most k distinct values: each right end r adds r - l + 1.
long long countWindows(const vector<int>& a, int k) {
    map<int, int> cnt;  // value -> how many times it occurs in a[l..r]
    int l = 0;
    long long total = 0;  // up to n(n+1)/2, about 2*10^10 for n = 2*10^5
    for (int r = 0; r < (int)a.size(); r++) {
        cnt[a[r]]++;
        while ((int)cnt.size() > k) {  // too many distinct values: shrink
            if (--cnt[a[l]] == 0) cnt.erase(a[l]);
            l++;
        }
        total += r - l + 1;  // every left end in [l, r] is valid
    }
    return total;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << countWindows(a, k) << "\n";
}
