/*
Problem: print the maximum of every window of k consecutive elements.
Input: n k (1 <= k <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: n - k + 1 maxima.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    deque<int> dq;  // positions in the window that are not dominated; values decrease front to back
    vector<long long> out;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();  // dominated by i from now on
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();  // left the window [i - k + 1, i]
        if (i >= k - 1) out.push_back(a[dq.front()]);  // Theorem 1.6.3
    }
    for (int j = 0; j < (int)out.size(); j++) cout << out[j] << (j + 1 < (int)out.size() ? ' ' : '\n');
}
