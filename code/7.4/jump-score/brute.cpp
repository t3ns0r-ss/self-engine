#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n), dp(n, LLONG_MIN);
    for (long long& x : a) cin >> x;
    dp[0] = a[0];
    for (int i = 1; i < n; i++)
        for (int j = max(0, i - k); j < i; j++) dp[i] = max(dp[i], dp[j] + a[i]);
    cout << dp[n - 1] << "\n";
}
