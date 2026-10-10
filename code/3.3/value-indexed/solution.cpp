/*
Problem: the same knapsack, but weights are huge and values small: n items with weights w_i and values v_i,
each at most once, total weight at most W; maximise the total value.
Input: n W (1 <= n <= 100, 1 <= W <= 10^9), then n lines w_i v_i (1 <= w_i <= W, 1 <= v_i <= 1000).
Output: the largest total value.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.2. Weights are huge, values small: minw[t] = the least weight of a subset with total value exactly t.
int valueIndexed(const vector<long long>& w, const vector<int>& v, long long W) {
    int n = w.size(), V = accumulate(v.begin(), v.end(), 0);
    const long long INF = LLONG_MAX / 2;  // "no subset has this value"; halved so INF + w cannot overflow
    vector<long long> minw(V + 1, INF);
    minw[0] = 0;
    for (int i = 0; i < n; i++)
        for (int t = V; t >= v[i]; t--) minw[t] = min(minw[t], minw[t - v[i]] + w[i]);
    int answer = 0;
    for (int t = 0; t <= V; t++)
        if (minw[t] <= W) answer = t;  // the largest value whose lightest subset fits
    return answer;
}
// snippet:end

int main() {
    int n;
    long long W;
    cin >> n >> W;
    vector<long long> w(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    cout << valueIndexed(w, v, W) << "\n";
}
