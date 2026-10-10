/*
Problem: CSES 1074 Stick Lengths. Make all n sticks the same length; changing a length by x costs x.
Input: n (1 <= n <= 2*10^5), then p_1 .. p_n (1 <= p_i <= 10^9).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The cheapest common length for all sticks, with the cost |p_i - target| per stick: a median is optimal.
long long stickCost(vector<long long> p) {
    sort(p.begin(), p.end());
    long long target = p[p.size() / 2];  // a median is an optimal length
    long long cost = 0;                  // up to 2*10^5 * 10^9 = 2*10^14
    for (long long x : p) cost += llabs(x - target);
    return cost;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    cout << stickCost(p) << "\n";
}
