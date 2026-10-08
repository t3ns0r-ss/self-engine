/*
Problem: give each of n jobs to one of k workers so that the largest total load is as small as possible.
Input: n k (1 <= n <= 12, 1 <= k <= n), then n job lengths (1 <= length <= 10^8).
Output: the smallest possible largest load.
*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> job, load;  // loads can reach 12 * 10^8, more than int holds
long long best;

void rec(int i, long long currentMax) {
    if (currentMax >= best) return;  // bound: loads only grow, so this branch cannot beat best (Theorem 3.1.3)
    if (i == n) {
        best = currentMax;  // a complete assignment that is better
        return;
    }
    for (int w = 0; w < k; w++) {
        // symmetry: workers with equal loads are interchangeable, so try only the first of them
        bool seen = false;
        for (int v = 0; v < w; v++)
            if (load[v] == load[w]) seen = true;
        if (seen) continue;
        load[w] += job[i];
        rec(i + 1, max(currentMax, load[w]));
        load[w] -= job[i];  // undo
    }
}

int main() {
    cin >> n >> k;
    job.resize(n);
    for (auto& x : job) cin >> x;
    sort(job.rbegin(), job.rend());  // longest jobs first: a good answer is found early
    load.assign(k, 0);
    best = LLONG_MAX;
    rec(0, 0);
    cout << best << "\n";
}
