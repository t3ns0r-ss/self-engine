/*
Problem: CSES 1644 Maximum Subarray Sum II. The largest sum of a subarray whose length is between
a and b.
Input: n a b (1 <= a <= b <= n <= 2*10^5), then x_1 .. x_n (|x_i| <= 10^9).
Output: the largest sum.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1644. p: prefix sums (p[0] = 0). Largest p[r] - p[l] with a <= r - l <= b.
long long bestLengthRange(const vector<long long>& p, int a, int b) {
    int n = p.size() - 1;
    deque<int> dq;  // candidate starts l in [r - b, r - a]; p values increase front to back
    long long best = LLONG_MIN;
    for (int r = a; r <= n; r++) {
        int l = r - a;  // the start that becomes allowed now
        while (!dq.empty() && p[dq.back()] >= p[l]) dq.pop_back();
        dq.push_back(l);
        if (dq.front() < r - b) dq.pop_front();  // too long
        best = max(best, p[r] - p[dq.front()]);
    }
    return best;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        p[i] = p[i - 1] + x;
    }
    cout << bestLengthRange(p, a, b) << "\n";
}
