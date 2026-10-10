/*
Problem: CSES 1140, Projects. Each of n projects runs from day a_i to day b_i and pays p_i; no two attended projects
may share a day. Print the largest total pay.
Input: n (n <= 2 * 10^5), then n lines a_i b_i p_i (1 <= a_i <= b_i <= 10^9, 1 <= p_i <= 10^9).
Output: the largest total pay.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1140. Sort the projects by end day; best[i] = the largest pay using only the first i projects: skip project i, or
// take it after the first j projects, which end before it starts (found by binary search).
long long projects(vector<array<long long, 3>> pr) {  // each {end, start, pay}
    sort(pr.begin(), pr.end());
    int n = pr.size();
    vector<long long> ends(n);
    for (int i = 0; i < n; i++) ends[i] = pr[i][0];
    vector<long long> best(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int j = lower_bound(ends.begin(), ends.end(), pr[i - 1][1]) - ends.begin();
        best[i] = max(best[i - 1], best[j] + pr[i - 1][2]);
    }
    return best[n];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> pr(n);
    for (auto& p : pr) cin >> p[1] >> p[0] >> p[2];
    cout << projects(pr) << "\n";
}
