#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int best = 0;
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));
    for (size_t i = 1; i <= a.size(); i++)
        for (size_t j = 1; j <= b.size(); j++)
            if (a[i - 1] == b[j - 1]) best = max(best, dp[i][j] = dp[i - 1][j - 1] + 1);
    cout << best << "\n";
}
