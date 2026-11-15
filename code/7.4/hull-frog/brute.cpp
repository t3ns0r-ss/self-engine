#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long C;
    cin >> n >> C;
    vector<long long> h(n), dp(n, LLONG_MAX);
    for (long long& x : h) cin >> x;
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++) dp[i] = min(dp[i], dp[j] + (h[i] - h[j]) * (h[i] - h[j]) + C);
    cout << dp[n - 1] << "\n";
}
