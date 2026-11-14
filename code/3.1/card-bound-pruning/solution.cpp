#include <bits/stdc++.h>
using namespace std;

long long minMaxLoad(vector<long long> job, int k) {
    int n = job.size();
    sort(job.rbegin(), job.rend());
    vector<long long> load(k, 0);
    long long best = LLONG_MAX;
    function<void(int, long long)> rec = [&](int i, long long currentMax) {
        if (currentMax >= best) return;
        if (i == n) { best = currentMax; return; }
        for (int w = 0; w < k; w++) {
            bool seen = false;
            for (int v = 0; v < w; v++) if (load[v] == load[w]) seen = true;
            if (seen) continue;
            load[w] += job[i];
            rec(i + 1, max(currentMax, load[w]));
            load[w] -= job[i];
        }
    };
    rec(0, 0);
    return best;
}
long long bruteLoad(const vector<long long>& job, int k) {
    int n = job.size();
    long long want = LLONG_MAX, total = 1;
    for (int i = 0; i < n; i++) total *= k;
    for (long long code = 0; code < total; code++) {
        vector<long long> load(k, 0);
        long long x = code;
        for (int i = 0; i < n; i++) load[x % k] += job[i], x /= k;
        want = min(want, *max_element(load.begin(), load.end()));
    }
    return want;
}
// the same search with an estimate that is not optimistic: "current largest load + the next job" assumes the next job lands on the most loaded worker
long long minMaxLoadBadCut(vector<long long> job, int k) {
    int n = job.size();
    sort(job.rbegin(), job.rend());
    vector<long long> load(k, 0);
    long long best = LLONG_MAX;
    function<void(int, long long)> rec = [&](int i, long long currentMax) {
        if (i < n && currentMax + job[i] >= best) return;
        if (currentMax >= best) return;
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
int main() {
    // P1: 5 jobs 8 7 5 4 3 on 2 workers. P2: 5 jobs 5 5 4 3 3 on 3 workers. Brute: every assignment. Method: branch and bound.
    cout << "P1 brute=" << bruteLoad({8, 7, 5, 4, 3}, 2) << " method=" << minMaxLoad({8, 7, 5, 4, 3}, 2) << '\n';
    cout << "P2 brute=" << bruteLoad({5, 5, 4, 3, 3}, 3) << " method=" << minMaxLoad({5, 5, 4, 3, 3}, 3) << '\n';
    // N1: 3 jobs 8 1 1 on 3 workers. The cut "current largest load + the next job >= best" is not an optimistic estimate: it throws away the answer 8.
    cout << "N1 brute=" << bruteLoad({8, 1, 1}, 3) << " method=" << minMaxLoadBadCut({8, 1, 1}, 3) << '\n';
}
