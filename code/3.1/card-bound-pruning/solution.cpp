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
// largest subset sum <= T by branch and bound with the estimate "sum so far + all the rest"; gives up after cap calls
long long boundSubsetSum(vector<long long> a, long long T, long long cap, bool& gaveUp) {
    int n = a.size();
    sort(a.rbegin(), a.rend());
    vector<long long> rest(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) rest[i] = rest[i + 1] + a[i];
    long long best = 0, calls = 0;
    gaveUp = false;
    function<void(int, long long)> rec = [&](int i, long long sum) {
        if (gaveUp) return;
        if (++calls > cap) { gaveUp = true; return; }
        best = max(best, sum);
        if (i == n || sum + rest[i] <= best) return;  // the estimate cannot beat best
        if (sum + a[i] <= T) rec(i + 1, sum + a[i]);
        rec(i + 1, sum);
    };
    rec(0, 0);
    return best;
}
long long mitmBest(const vector<long long>& a, long long T) {
    int n = a.size();
    auto sums = [&](int from, int to) {
        vector<long long> s = {0};
        for (int i = from; i < to; i++) { int sz = s.size(); for (int j = 0; j < sz; j++) s.push_back(s[j] + a[i]); }
        return s;
    };
    auto L = sums(0, n / 2), R = sums(n / 2, n);
    sort(R.begin(), R.end());
    long long best = 0;
    for (long long x : L) if (x <= T) best = max(best, x + *prev(upper_bound(R.begin(), R.end(), T - x)));
    return best;
}
int main() {
    // P1: 5 jobs 8 7 5 4 3 on 2 workers. P2: 5 jobs 5 5 4 3 3 on 3 workers. Brute: every assignment. Method: branch and bound.
    cout << "P1 brute=" << bruteLoad({8, 7, 5, 4, 3}, 2) << " method=" << minMaxLoad({8, 7, 5, 4, 3}, 2) << '\n';
    cout << "P2 brute=" << bruteLoad({5, 5, 4, 3, 3}, 3) << " method=" << minMaxLoad({5, 5, 4, 3, 3}, 3) << '\n';
    // N1: the largest subset sum at most T of 36 large values; the bound "sum so far + the rest" rarely cuts, so it gives up.
    mt19937_64 rng(12345);
    vector<long long> a(36);
    long long total = 0;
    for (auto& x : a) x = 500000000 + rng() % 500000000, total += x;
    bool gaveUp;
    long long T = total / 2;
    boundSubsetSum(a, T, 5000000, gaveUp);
    cout << "N1 brute=" << mitmBest(a, T) << " method=" << (gaveUp ? "too-slow" : "ok") << '\n';
}
