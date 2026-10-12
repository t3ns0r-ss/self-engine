#include <bits/stdc++.h>
using namespace std;

/*
Problem: n segments [l_i, r_i] of integer points (points from 1 to 2·10^5) and a number k. Remove the fewest segments so that no point
is covered by more than k of the remaining ones. Print that number.
Input: n and k, then the n segments "l r".
Output: the fewest segments to remove.
*/


// snippet:begin
// Theorem 7.4.1 (drop the worst) in a sweep over the points: the ordered multiset holds the right ends of the segments that cover the
// point; when more than k cover it, the segment that reaches farthest to the right is dropped (it would trouble the most points ahead).
int fewestRemovals(vector<pair<int, int>> segments, int k) {
    sort(segments.begin(), segments.end());
    multiset<int> active;
    int removed = 0;
    size_t next = 0;
    for (int point = 1; next < segments.size() || !active.empty(); point++) {
        while (next < segments.size() && segments[next].first == point) active.insert(segments[next++].second);
        while (!active.empty() && *active.begin() < point) active.erase(active.begin());  // ended before the point
        while ((int)active.size() > k) active.erase(prev(active.end())), removed++;
    }
    return removed;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> segments(n);
    for (auto& [l, r] : segments) cin >> l >> r;
    cout << fewestRemovals(segments, k) << "\n";
}
