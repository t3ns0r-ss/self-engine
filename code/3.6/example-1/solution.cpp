/*
Problem: AtCoder EDPC N, Slimes. N slimes in a row with sizes a_1..a_N; combining two neighbours of sizes x and y
gives one slime of size x + y and costs x + y. Combine all of them into one slime at the least total cost.
Input: N (2 <= N <= 400), then a_1..a_N (1 <= a_i <= 10^9).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// EDPC N. best[l][r] = the least cost to combine slimes l..r into one: the last combination joins [l, k] and [k + 1, r] and
// costs the total size, found with prefix sums.
long long slimes(const vector<long long>& a) {
    int n = a.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + a[i - 1];
    vector<vector<long long>> best(n + 2, vector<long long>(n + 2, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            long long low = LLONG_MAX;
            for (int k = l; k < r; k++) low = min(low, best[l][k] + best[k + 1][r]);
            best[l][r] = low + prefix[r] - prefix[l - 1];
        }
    return best[1][n];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << slimes(a) << "\n";
}
