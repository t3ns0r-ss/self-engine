/*
Problem: print the maximum of every window of k consecutive elements.
Input: n k (1 <= k <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: n - k + 1 maxima.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.3. Maximum of every window of k consecutive elements.
vector<long long> windowMax(const vector<long long>& a, int k) {
    deque<int> dq;  // positions not dominated by a later one; values decrease from front to back
    vector<long long> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();  // left the window [i - k + 1, i]
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<long long> out = windowMax(a, k);
    for (int j = 0; j < (int)out.size(); j++) cout << out[j] << (j + 1 < (int)out.size() ? ' ' : '\n');
}
