#include <bits/stdc++.h>
using namespace std;

/*
Problem: n houses stand on a line at the increasing positions x_1 < ... < x_n. Place k mailboxes at houses. Each house uses the
nearest mailbox. Print the least possible sum of the distances from the houses to their mailboxes.
Input: n and k, then the n positions.
Output: the least total distance.
*/

const long long INF = LLONG_MAX / 4;

// snippet:begin
// Theorem 7.3.7. The houses j+1..i form one group served by its median house, so cost(j, i) is the sum of the distances to the
// median, and it is read from prefix sums of the positions in O(1). Layers t = 1..k are filled by the divide and conquer.
vector<long long> X, S;  // X[i] = position of house i (1-based), S = prefix sums of X
long long cost(int j, int i) {
    int m = (j + 1 + i) / 2;  // the median house of j+1..i
    return (X[m] * (m - j) - (S[m] - S[j])) + ((S[i] - S[m]) - X[m] * (i - m));
}
void fillLayer(int lo, int hi, int optLo, int optHi, const vector<long long>& prev, vector<long long>& cur) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2, bestJ = optLo;
    long long best = INF;
    for (int j = optLo; j <= min(mid - 1, optHi); j++) {
        long long cand = prev[j] + cost(j, mid);
        if (cand < best) { best = cand; bestJ = j; }
    }
    cur[mid] = best;
    fillLayer(lo, mid - 1, optLo, bestJ, prev, cur);
    fillLayer(mid + 1, hi, bestJ, optHi, prev, cur);
}
long long mailboxes(const vector<long long>& pos, int k) {
    int n = pos.size();
    X.assign(n + 1, 0);
    S.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) { X[i] = pos[i - 1]; S[i] = S[i - 1] + X[i]; }
    vector<long long> prev(n + 1, INF), cur(n + 1, INF);
    for (int i = 1; i <= n; i++) prev[i] = cost(0, i);
    for (int t = 2; t <= k; t++) {
        fillLayer(t, n, t - 1, n - 1, prev, cur);
        prev = cur;
    }
    return prev[n];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> pos(n);
    for (long long& x : pos) cin >> x;
    cout << mailboxes(pos, k) << "\n";
}
