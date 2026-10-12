#include <bits/stdc++.h>
using namespace std;

// method: the card's recurrence with a deque: the window [i - k, i - 1] only moves right, and an expired index never comes back.
// start = true: a path may start anywhere (dp = a[i] + max(0, ...)); start = false: the path must start at the cell 0.
long long method(const vector<long long>& a, const vector<int>& left, bool start) {
    int n = a.size();
    vector<long long> dp(n);
    deque<int> window;
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        while (!window.empty() && window.front() < left[i]) window.pop_front();
        long long from = window.empty() ? (start ? 0 : LLONG_MIN / 4) : (start ? max(0LL, dp[window.front()]) : dp[window.front()]);
        dp[i] = i == 0 && !start ? a[0] : a[i] + from;
        while (!window.empty() && dp[window.back()] <= dp[i]) window.pop_back();
        window.push_back(i);
        best = max(best, dp[i]);
    }
    return start ? best : dp[n - 1];
}
// brute: the definition, a maximum over the whole allowed range [left[i], i - 1] for each i.
long long brute(const vector<long long>& a, const vector<int>& left, bool start) {
    int n = a.size();
    vector<long long> dp(n, LLONG_MIN / 4);
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long from = start ? 0 : LLONG_MIN / 4;
        for (int j = left[i]; j < i; j++) from = max(from, dp[j]);
        dp[i] = i == 0 && !start ? a[0] : a[i] + from;
        best = max(best, dp[i]);
    }
    return start ? best : dp[n - 1];
}
vector<int> fixedWindow(int n, int k) {
    vector<int> left(n);
    for (int i = 0; i < n; i++) left[i] = max(0, i - k);
    return left;
}
int main() {
    vector<long long> a1 = {10, 2, -10, 5, 20}, a2 = {10, -5, -2, 4, 0}, a3 = {5, -10, 1, 1};
    cout << "P1 brute=" << brute(a1, fixedWindow(5, 2), true) << " method=" << method(a1, fixedWindow(5, 2), true) << "\n";
    cout << "P2 brute=" << brute(a2, fixedWindow(5, 3), false) << " method=" << method(a2, fixedWindow(5, 3), false) << "\n";
    vector<int> left3 = {0, 0, 1, 0};  // the allowed range of each i is not monotone: i = 3 may look back to 0 again
    cout << "N1 brute=" << brute(a3, left3, false) << " method=" << method(a3, left3, false) << "\n";
}
