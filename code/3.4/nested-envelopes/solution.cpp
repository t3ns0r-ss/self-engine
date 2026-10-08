/*
Problem: the largest number of envelopes that can be nested one inside another; an envelope fits into another
when both its width and its height are strictly smaller. Envelopes cannot be rotated.
Input: n (1 <= n <= 2 * 10^5), then n lines w_i h_i (1 <= w_i, h_i <= 10^9).
Output: the largest nesting.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> e(n);
    for (auto& [w, h] : e) cin >> w >> h;
    // width increasing; equal widths by height decreasing, so they can never follow each other (Theorem 3.4.3)
    sort(e.begin(), e.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
        if (p.first != q.first) return p.first < q.first;
        return p.second > q.second;
    });
    vector<int> tails;  // strict LIS of the heights in this order
    for (auto& [w, h] : e) {
        auto it = lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    cout << tails.size() << "\n";
}
