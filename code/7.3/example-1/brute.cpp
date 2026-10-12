#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    vector<long long> a(n), dp(n);
    for (int& x : h) cin >> x;
    for (long long& x : a) cin >> x;
    long long best = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = a[i];
        for (int j = 0; j < i; j++)
            if (h[j] < h[i]) dp[i] = max(dp[i], dp[j] + a[i]);
        best = max(best, dp[i]);
    }
    cout << best << "\n";
}
