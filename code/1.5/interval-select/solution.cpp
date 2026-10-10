/*
Problem: n closed intervals [s_i, e_i]; two intervals overlap if they share a point. Print the largest
number of pairwise non-overlapping intervals, and the fewest points that hit every interval.
Input: n (1 <= n <= 2*10^5), then n lines "s_i e_i" (0 <= s_i <= e_i <= 10^9).
Output: "maxDisjoint minPoints" (the two are equal by Theorem 1.5.2).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.2. The largest number of pairwise disjoint closed intervals (touching counts as overlapping); the same
// number of points hits every interval.
int intervalSelect(vector<pair<int, int>> iv) {  // (start, end)
    sort(iv.begin(), iv.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; });
    int chosen = 0;
    long long lastEnd = -1;  // end of the last chosen interval; also the last point placed
    for (auto [s, e] : iv)
        if (s > lastEnd) {  // compatible: starts after the last chosen one ends
            chosen++;
            lastEnd = e;    // earliest end first
        }
    return chosen;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> iv(n);
    for (auto& [s, e] : iv) cin >> s >> e;
    int k = intervalSelect(iv);
    cout << k << " " << k << "\n";
}
