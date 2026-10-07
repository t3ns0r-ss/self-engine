/*
Problem: the length of the longest subarray whose maximum minus minimum is at most K.
Input: n K (1 <= n <= 2*10^5, 0 <= K <= 2*10^9), then a_1 .. a_n (|a_i| <= 10^9).
Output: the largest length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    deque<int> mx, mn;  // window maximum and minimum candidates (Theorem 1.6.3)
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        while (!mx.empty() && a[mx.back()] <= a[r]) mx.pop_back();
        mx.push_back(r);
        while (!mn.empty() && a[mn.back()] >= a[r]) mn.pop_back();
        mn.push_back(r);
        // "max - min <= K" is closed under shrinking: shrink from the left until it holds (topic 1.3)
        while (a[mx.front()] - a[mn.front()] > K) {
            l++;
            if (mx.front() < l) mx.pop_front();  // the left end passed it
            if (mn.front() < l) mn.pop_front();
        }
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
