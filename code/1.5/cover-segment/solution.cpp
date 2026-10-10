/*
Problem: cover the segment [0, L] with as few of the n given segments [l_i, r_i] as possible (their
union must contain every point of [0, L]); print that number, or -1 if it cannot be covered.
Input: n L (1 <= n <= 2*10^5, 1 <= L <= 10^9), then n lines "l_i r_i" (0 <= l_i <= r_i <= 10^9).
Output: the fewest segments, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.5. The fewest segments that cover [0, L], or -1: among the segments starting inside the covered part,
// take the one reaching farthest (a larger reach dominates a smaller one).
int coverSegment(vector<pair<long long, long long>> seg, long long L) {
    sort(seg.begin(), seg.end());  // by left end
    long long reach = 0;           // [0, reach] is covered by the segments chosen so far
    int used = 0, i = 0, n = seg.size();
    while (reach < L) {
        long long best = reach;
        while (i < n && seg[i].first <= reach) best = max(best, seg[i++].second);
        if (best == reach) break;  // nothing extends the cover: a gap
        reach = best;
        used++;
    }
    return reach >= L ? used : -1;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long L;
    cin >> n >> L;
    vector<pair<long long, long long>> seg(n);
    for (auto& [l, r] : seg) cin >> l >> r;
    cout << coverSegment(seg, L) << "\n";
}
