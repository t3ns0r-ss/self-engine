/*
Problem: n jobs with durations t_i and weights w_i are done one after another from time 0. Choose the
order that minimises the sum of w_i * (finishing time of job i); print that sum.
Input: n (1 <= n <= 2*10^5), then n lines "t_i w_i" (1 <= t_i, w_i <= 10^4).
Output: the minimum weighted sum.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> job(n);  // (t, w)
    for (auto& [t, w] : job) cin >> t >> w;
    // x before y when t_x / w_x < t_y / w_y, compared exactly as t_x * w_y < t_y * w_x
    // (swapping adjacent x, y changes the sum by w_x * t_y - w_y * t_x, Theorem 1.5.1)
    sort(job.begin(), job.end(), [](const pair<long long, long long>& x, const pair<long long, long long>& y) {
        return x.first * y.second < y.first * x.second;
    });
    long long time = 0, total = 0;  // total up to 10^4 * (2*10^5 * 10^4) * 2*10^5, about 4*10^18
    for (auto [t, w] : job) {
        time += t;
        total += w * time;
    }
    cout << total << "\n";
}
