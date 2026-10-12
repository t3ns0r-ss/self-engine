#include <bits/stdc++.h>
using namespace std;

/*
Problem: n cells with integer numbers a_i (possibly negative). Start in cell 0 and jump forward by 1 to k cells at a time. The score
is the sum of the numbers of all cells visited, both ends included. Print the largest score of a path from cell 0 to cell n - 1.
Input: n and k, then the n numbers.
Output: the largest score.
*/


// snippet:begin
// Theorem 7.3.2: dp[i] = a[i] + max dp[j] over i - k <= j <= i - 1; the deque keeps the window's indices with decreasing dp.
long long bestJumps(const vector<long long>& a, int k) {
    int n = a.size();
    vector<long long> dp(n);
    dp[0] = a[0];
    deque<int> window = {0};
    for (int i = 1; i < n; i++) {
        while (window.front() < i - k) window.pop_front();  // left the window; i - 1 is always inside
        dp[i] = a[i] + dp[window.front()];
        while (!window.empty() && dp[window.back()] <= dp[i]) window.pop_back();
        window.push_back(i);
    }
    return dp[n - 1];
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long& x : a) cin >> x;
    cout << bestJumps(a, k) << "\n";
}
