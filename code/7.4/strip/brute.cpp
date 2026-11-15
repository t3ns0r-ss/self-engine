#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s, l;
    cin >> n >> s >> l;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int hi = INT_MIN, lo = INT_MAX;
        for (int j = i - 1; j >= 0; j--) {  // the piece a[j..i)
            hi = max(hi, a[j]), lo = min(lo, a[j]);
            if (hi - lo > s) break;
            if (i - j >= l && dp[j] < INF) dp[i] = min(dp[i], dp[j] + 1);
        }
    }
    cout << (dp[n] < INF ? dp[n] : -1) << "\n";
}
