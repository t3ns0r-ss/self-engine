/*
Problem: n closed intervals [s_i, e_i]; two intervals overlap if they share a point. Print the largest
number of pairwise non-overlapping intervals, and the fewest points that hit every interval.
Input: n (1 <= n <= 2*10^5), then n lines "s_i e_i" (0 <= s_i <= e_i <= 10^9).
Output: "maxDisjoint minPoints" (the two are equal by Theorem 1.5.2).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> iv(n);  // stored as (end, start) so that sorting orders by end
    for (auto& [e, s] : iv) cin >> s >> e;
    sort(iv.begin(), iv.end());
    int chosen = 0;
    long long lastEnd = -1;  // end of the last chosen interval; also the last point placed
    for (auto [e, s] : iv)
        if (s > lastEnd) {  // compatible: starts after the last chosen one ends (touching overlaps)
            chosen++;
            lastEnd = e;    // earliest end first; a point placed at e hits every interval skipped until the next choice
        }
    cout << chosen << " " << chosen << "\n";
}
