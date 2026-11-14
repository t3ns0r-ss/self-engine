#include <bits/stdc++.h>
using namespace std;

/*
Problem: n stones in a row with strictly increasing heights h_i, and a number C. A frog starts on stone 1 and jumps forward, from any
stone to any later stone; a jump from stone j to stone i costs (h_i - h_j)^2 + C. Print the least total cost to reach stone n.
Input: n and C, then the n heights.
Output: the least total cost.
*/


// snippet:begin
// Theorem 7.3.5. dp[i] = min over j < i of dp[j] + (h[i] - h[j])^2 + C. For a fixed j the part that depends on x = h[i] is
// the line (-2 h[j]) x + (dp[j] + h[j]^2). The slopes fall as j grows and the queries x rise, so a deque of lines is enough.
long long frogCost(const vector<long long>& h, long long C) {
    int n = h.size();
    vector<long long> dp(n, 0);
    using Line = array<long long, 2>;  // {slope, intercept}
    auto at = [](const Line& l, long long x) { return l[0] * x + l[1]; };
    auto useless = [](const Line& p, const Line& q, const Line& r) {  // q is never strictly the lowest of the three
        return (__int128)(q[1] - p[1]) * (q[0] - r[0]) >= (__int128)(r[1] - q[1]) * (p[0] - q[0]);
    };
    deque<Line> hull = {{-2 * h[0], h[0] * h[0]}};
    for (int i = 1; i < n; i++) {
        while (hull.size() >= 2 && at(hull[1], h[i]) <= at(hull[0], h[i])) hull.pop_front();
        dp[i] = at(hull.front(), h[i]) + h[i] * h[i] + C;
        Line now = {-2 * h[i], dp[i] + h[i] * h[i]};
        while (hull.size() >= 2 && useless(hull[hull.size() - 2], hull.back(), now)) hull.pop_back();
        hull.push_back(now);
    }
    return dp[n - 1];
}
// snippet:end

int main() {
    int n;
    long long C;
    cin >> n >> C;
    vector<long long> h(n);
    for (long long& x : h) cin >> x;
    cout << frogCost(h, C) << "\n";
}
