/*
Problem: choose m of n distinct positions on a line so that the smallest distance between two
chosen positions is as large as possible; print that distance.
Input: n m (2 <= m <= n <= 2*10^5), then n distinct positions (0 <= p_i <= 10^9).
Output: the largest possible smallest distance.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    sort(p.begin(), p.end());
    // ok(d): can m positions be chosen with all gaps >= d? Take the first position, then always the
    // next one at distance >= d from the last chosen (Lemma 1.4.4, second form). O(n).
    auto ok = [&](long long d) {
        int chosen = 1;
        long long last = p[0];
        for (int i = 1; i < n; i++)
            if (p[i] - last >= d) {
                chosen++;
                last = p[i];
            }
        return chosen >= m;
    };
    // ok is true, ..., true, false, ...: keep ok(lo) true and ok(hi) false; the answer is lo.
    long long lo = 0, hi = p[n - 1] - p[0] + 1;  // ok(0) holds; a gap above the span is impossible
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (ok(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo << "\n";
}
