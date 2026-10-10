#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.3. Tabulation in increasing order: every transition goes from a smaller (i, j) to a larger one. The number of
// lattice paths to (i, j) is the sum of the paths to (i - 1, j) and (i, j - 1).
long long gridPaths(int rows, int cols) {
    vector<vector<long long>> dp(rows + 1, vector<long long>(cols + 1, 0));
    dp[0][0] = 1;  // base case
    for (int i = 0; i <= rows; i++)
        for (int j = 0; j <= cols; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    return dp[rows][cols];
}
// snippet:end

long long brute(int i, int j) { return i < 0 || j < 0 ? 0 : (i == 0 && j == 0) ? 1 : brute(i - 1, j) + brute(i, j - 1); }
int main() {
    cout << "paths to (2, 2): " << gridPaths(2, 2) << ", paths to (3, 3): " << gridPaths(3, 3) << '\n';
    for (int i = 0; i <= 7; i++) for (int j = 0; j <= 7; j++) if (gridPaths(i, j) != brute(i, j)) return 1;
}
