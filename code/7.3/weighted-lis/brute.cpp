#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> w(n), dp(n);
    for (int& x : a) cin >> x;
    for (long long& x : w) cin >> x;
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        dp[i] = w[i];
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + w[i]);
        best = max(best, dp[i]);
    }
    cout << best << "\n";
}
