#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.3. Branch and bound for the smallest largest load: a branch is cut when its current largest load, which
// can only grow, is already >= best. Jobs are tried longest first.
long long minMaxLoad(vector<long long> job, int k, long long& calls) {
    int n = job.size();
    sort(job.rbegin(), job.rend());
    vector<long long> load(k, 0);
    long long best = LLONG_MAX;
    function<void(int, long long)> rec = [&](int i, long long currentMax) {
        calls++;
        if (currentMax >= best) return;  // the bound
        if (i == n) { best = currentMax; return; }
        for (int w = 0; w < k; w++) {
            load[w] += job[i];
            rec(i + 1, max(currentMax, load[w]));
            load[w] -= job[i];
        }
    };
    rec(0, 0);
    return best;
}
// snippet:end

int main() {
    long long calls = 0;
    long long best = minMaxLoad({8, 7, 5, 4, 3}, 2, calls);
    cout << "jobs 8 7 5 4 3 on 2 workers: smallest largest load " << best << ", " << calls << " calls (the tree has 63 nodes)\n";
    mt19937 rng(2);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 7, k = 1 + rng() % 3;
        vector<long long> job(n);
        for (auto& x : job) x = 1 + rng() % 9;
        long long want = LLONG_MAX;
        long long total = 1;
        for (int i = 0; i < n; i++) total *= k;
        for (long long code = 0; code < total; code++) {
            vector<long long> load(k, 0);
            long long x = code;
            for (int i = 0; i < n; i++) load[x % k] += job[i], x /= k;
            want = min(want, *max_element(load.begin(), load.end()));
        }
        long long c = 0;
        if (minMaxLoad(job, k, c) != want) return 1;
    }
}
