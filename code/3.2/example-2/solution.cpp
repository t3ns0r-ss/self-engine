/*
Problem: CSES 1140, Projects. Each of n projects runs from day a_i to day b_i and pays p_i; no two attended projects
may share a day. Print the largest total pay.
Input: n (n <= 2 * 10^5), then n lines a_i b_i p_i (1 <= a_i <= b_i <= 10^9, 1 <= p_i <= 10^9).
Output: the largest total pay.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> pr(n);  // {end, start, pay}, so sorting orders by end day
    for (auto& p : pr) cin >> p[1] >> p[0] >> p[2];
    sort(pr.begin(), pr.end());
    vector<long long> ends(n);
    for (int i = 0; i < n; i++) ends[i] = pr[i][0];
    // best[i] = largest pay using only the first i projects in order of end day (Theorem 3.2.1)
    vector<long long> best(n + 1, 0);  // totals up to 2 * 10^14: long long
    for (int i = 1; i <= n; i++) {
        long long start = pr[i - 1][1], pay = pr[i - 1][2];
        // projects that end before 'start' are a prefix of the sorted list: count them by binary search
        int j = lower_bound(ends.begin(), ends.end(), start) - ends.begin();
        best[i] = max(best[i - 1], best[j] + pay);  // skip project i, or take it after the first j
    }
    cout << best[n] << "\n";
}
