/*
Problem: the maximum of every segment of length exactly k.
Input: n k (1 <= k <= n), then n integers a[0..n-1].
Output: n - k + 1 numbers, the maximum of a[0..k-1], a[1..k], ...
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    multiset<int> window;  // the values of the current window, duplicates kept
    vector<int> out;
    for (int r = 0; r < n; r++) {
        window.insert(a[r]);
        if (r >= k) window.erase(window.find(a[r - k]));  // remove one copy only
        if (r >= k - 1) out.push_back(*window.rbegin());   // largest element
    }
    for (int i = 0; i < (int)out.size(); i++) cout << out[i] << (i + 1 < (int)out.size() ? ' ' : '\n');
}
