/*
Problem: two players alternately take the first or the last number of a row; each wants the largest total.
Print the first player's total when both play as well as possible.
Input: n (1 <= n <= 5000), then a_1..a_n (|a_i| <= 10^9).
Output: the first player's total.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.3. diff[l] = the score difference for the player to move on the segment [l, l + len - 1]; the first player's
// total is (sum + diff) / 2.
long long endGame(const vector<long long>& a) {
    int n = a.size();
    long long sum = accumulate(a.begin(), a.end(), 0LL);
    vector<long long> diff(a);  // length 1: take the only number
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            diff[l] = max(a[l] - diff[l + 1], a[r] - diff[l]);  // diff[l] still holds [l, r - 1]
        }
    return (sum + diff[0]) / 2;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << endGame(a) << "\n";
}
