/*
Problem: AtCoder EDPC N, Slimes. N slimes in a row with sizes a_1..a_N; combining two neighbours of sizes x and y
gives one slime of size x + y and costs x + y. Combine all of them into one slime at the least total cost.
Input: N (2 <= N <= 400), then a_1..a_N (1 <= a_i <= 10^9).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a;
        prefix[i] = prefix[i - 1] + a;
    }
    // best[l][r] = least cost to combine slimes l..r (1-based) into one
    vector<vector<long long>> best(n + 2, vector<long long>(n + 2, 0));
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            long long low = LLONG_MAX;
            for (int k = l; k < r; k++) low = min(low, best[l][k] + best[k + 1][r]);  // the last combination
            best[l][r] = low + prefix[r] - prefix[l - 1];                             // it costs the total size
        }
    }
    cout << best[1][n] << "\n";
}
