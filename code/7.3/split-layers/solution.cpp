#include <bits/stdc++.h>
using namespace std;

/*
Problem: n non-negative numbers are cut into exactly k non-empty groups of consecutive numbers. The cost of a group is the square of
the sum of its numbers. Print the least total cost.
Input: n and k, then the n numbers.
Output: the least total cost.
*/

const long long INF = LLONG_MAX / 4;

// snippet:begin
// Theorem 7.3.7. cur[i] = min over j < i of prev[j] + cost(j, i), where cost(j, i) = (P[i] - P[j])^2 for the prefix sums P.
// The best j never moves left as i grows, so after finding it for the middle i, the left half of the i's looks only at j <= best
// and the right half only at j >= best.
void fillLayer(int lo, int hi, int optLo, int optHi, const vector<long long>& prev, vector<long long>& cur, const vector<long long>& P) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2, bestJ = optLo;
    long long best = INF;
    for (int j = optLo; j <= min(mid - 1, optHi); j++) {
        long long cand = prev[j] + (P[mid] - P[j]) * (P[mid] - P[j]);
        if (cand < best) { best = cand; bestJ = j; }  // strict: keep the smallest best j
    }
    cur[mid] = best;
    fillLayer(lo, mid - 1, optLo, bestJ, prev, cur, P);
    fillLayer(mid + 1, hi, bestJ, optHi, prev, cur, P);
}
long long groupsCost(const vector<long long>& a, int k) {
    int n = a.size();
    vector<long long> P(n + 1, 0), prev(n + 1, INF), cur(n + 1, INF);
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + a[i];
    for (int i = 1; i <= n; i++) prev[i] = P[i] * P[i];  // one group
    for (int t = 2; t <= k; t++) {
        fillLayer(t, n, t - 1, n - 1, prev, cur, P);     // t groups: the last group starts after j >= t - 1
        prev = cur;
    }
    return prev[n];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long& x : a) cin >> x;
    cout << groupsCost(a, k) << "\n";
}
