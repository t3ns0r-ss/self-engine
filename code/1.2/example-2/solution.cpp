/*
Problem: LeetCode 42 Trapping Rain Water, as a program. Bars of width 1 with heights h_0 .. h_{n-1};
how much water stays on top of them after rain?
Input: n (1 <= n <= 2*10^4), then h_0 .. h_{n-1} (0 <= h_i <= 10^5).
Output: the amount of water.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> left(n), right(n);  // left[i] = max(h_0..h_i), right[i] = max(h_i..h_{n-1})
    for (int i = 0; i < n; i++) left[i] = max(i > 0 ? left[i - 1] : 0, h[i]);
    for (int i = n - 1; i >= 0; i--) right[i] = max(i + 1 < n ? right[i + 1] : 0, h[i]);
    long long water = 0;  // up to 2*10^4 * 10^5 = 2*10^9, beyond int
    for (int i = 0; i < n; i++) water += min(left[i], right[i]) - h[i];
    cout << water << "\n";
}
