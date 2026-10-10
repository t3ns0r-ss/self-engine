/*
Problem: the maximum of every segment of length exactly k.
Input: n k (1 <= k <= n), then n integers a[0..n-1].
Output: n - k + 1 numbers, the maximum of a[0..k-1], a[1..k], ...
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.3 with a multiset. The maximum of every window of k elements.
vector<int> windowMax(const vector<int>& a, int k) {
    multiset<int> window;  // the values of the current window, duplicates kept
    vector<int> out;
    for (int r = 0; r < (int)a.size(); r++) {
        window.insert(a[r]);
        if (r >= k) window.erase(window.find(a[r - k]));  // remove one copy only
        if (r >= k - 1) out.push_back(*window.rbegin());   // largest element
    }
    return out;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> out = windowMax(a, k);
    for (int i = 0; i < (int)out.size(); i++) cout << out[i] << (i + 1 < (int)out.size() ? ' ' : '\n');
}
