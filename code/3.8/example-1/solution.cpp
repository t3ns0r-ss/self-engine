/*
Problem: AtCoder EDPC O, Matching. N men and N women; a[i][j] = 1 if man i and woman j are compatible. Count the
ways to form N compatible man-woman pairs that use everyone exactly once, modulo 10^9 + 7.
Input: N (1 <= N <= 21), then the N x N matrix a of 0s and 1s.
Output: the count modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// EDPC O. ways[mask] = the ways for men 0..|mask|-1 to be paired with exactly the women in mask.
long long matching(const vector<vector<int>>& a) {
    const long long MOD = 1'000'000'007;
    int n = a.size();
    vector<long long> ways(1 << n, 0);
    ways[0] = 1;
    for (int mask = 0; mask < (1 << n) - 1; mask++) {
        if (ways[mask] == 0) continue;
        int man = __builtin_popcount(mask);  // the next man to pair
        for (int j = 0; j < n; j++)
            if (a[man][j] && !(mask >> j & 1)) ways[mask | 1 << j] = (ways[mask | 1 << j] + ways[mask]) % MOD;
    }
    return ways[(1 << n) - 1];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    cout << matching(a) << "\n";
}
