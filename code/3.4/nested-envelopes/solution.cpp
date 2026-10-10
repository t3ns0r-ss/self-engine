/*
Problem: the largest number of envelopes that can be nested one inside another; an envelope fits into another
when both its width and its height are strictly smaller. Envelopes cannot be rotated.
Input: n (1 <= n <= 2 * 10^5), then n lines w_i h_i (1 <= w_i, h_i <= 10^9).
Output: the largest nesting.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.3. Width increasing, equal widths by height decreasing, then the strict LIS of the heights.
int nestedEnvelopes(vector<pair<int, int>> e) {
    sort(e.begin(), e.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
        if (p.first != q.first) return p.first < q.first;
        return p.second > q.second;
    });
    vector<int> tails;
    for (auto& [w, h] : e) {
        auto it = lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    return tails.size();
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> e(n);
    for (auto& [w, h] : e) cin >> w >> h;
    cout << nestedEnvelopes(e) << "\n";
}
