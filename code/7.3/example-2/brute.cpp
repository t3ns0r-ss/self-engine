#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> nums(n), dp(n);
    for (long long& x : nums) cin >> x;
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        dp[i] = nums[i];
        for (int j = max(0, i - k); j < i; j++) dp[i] = max(dp[i], dp[j] + nums[i]);
        best = max(best, dp[i]);
    }
    cout << best << "\n";
}
