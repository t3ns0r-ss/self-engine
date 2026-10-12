#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.3.2. dp[i] = a[i] + max(0, max dp[j] over the window i-k <= j <= i-1). The deque holds indices of the window with
// decreasing dp from front to back, so the front is the maximum; an index behind a later, not smaller one is never the maximum.
vector<long long> windowBest(const vector<long long>& a, int k) {
    int n = a.size();
    vector<long long> dp(n);
    deque<int> window;
    for (int i = 0; i < n; i++) {
        while (!window.empty() && window.front() < i - k) window.pop_front();  // left the window
        dp[i] = a[i] + (window.empty() ? 0 : max(0LL, dp[window.front()]));
        while (!window.empty() && dp[window.back()] <= dp[i]) window.pop_back();
        window.push_back(i);
    }
    return dp;
}
// snippet:end

vector<long long> bruteWindow(const vector<long long>& a, int k) {
    int n = a.size();
    vector<long long> dp(n);
    for (int i = 0; i < n; i++) {
        long long best = 0;
        for (int j = max(0, i - k); j < i; j++) best = max(best, dp[j]);
        dp[i] = a[i] + best;
    }
    return dp;
}

int main() {
    auto show = [](const vector<long long>& a, int k) {
        auto dp = windowBest(a, k);
        cout << "dp:";
        for (long long x : dp) cout << " " << x;
        cout << "\nmost: " << *max_element(dp.begin(), dp.end()) << "\n";
    };
    show({10, 2, -10, 5, 20}, 2);
    show({-1, -2, -3}, 1);
    // Check (not printed): 3000 random arrays of up to 10 numbers and every window size, against the O(nk) definition.
    mt19937 rng(12);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 10 + 1, k = rng() % n + 1;
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 21) - 10;
        if (windowBest(a, k) != bruteWindow(a, k)) return 1;
    }
}
