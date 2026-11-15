#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto distinct = [&](int l, int r) {  // a[l..r)
        set<int> s(a.begin() + l, a.begin() + r);
        return (int)s.size();
    };
    const int NEG = -1e9;
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, NEG));
    dp[0][0] = 0;
    for (int c = 1; c <= k; c++)
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[c - 1][j] > NEG) dp[c][i] = max(dp[c][i], dp[c - 1][j] + distinct(j, i));
    cout << dp[k][n] << "\n";
}
