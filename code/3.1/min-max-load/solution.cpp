/*
Problem: give each of n jobs to one of k workers so that the largest total load is as small as possible.
Input: n k (1 <= n <= 12, 1 <= k <= n), then n job lengths (1 <= length <= 10^8).
Output: the smallest possible largest load.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.3. Branch and bound for the smallest largest load: loads only grow, so a branch whose current largest load
// is already >= best is cut. Longest jobs first; workers with equal loads are interchangeable, so only the first is tried.
long long minMaxLoad(vector<long long> job, int k) {
    int n = job.size();
    sort(job.rbegin(), job.rend());
    vector<long long> load(k, 0);
    long long best = LLONG_MAX;
    function<void(int, long long)> rec = [&](int i, long long currentMax) {
        if (currentMax >= best) return;  // bound
        if (i == n) {
            best = currentMax;
            return;
        }
        for (int w = 0; w < k; w++) {
            bool seen = false;
            for (int v = 0; v < w; v++) if (load[v] == load[w]) seen = true;
            if (seen) continue;
            load[w] += job[i];
            rec(i + 1, max(currentMax, load[w]));
            load[w] -= job[i];  // undo
        }
    };
    rec(0, 0);
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> job(n);
    for (auto& x : job) cin >> x;
    cout << minMaxLoad(job, k) << "\n";
}
