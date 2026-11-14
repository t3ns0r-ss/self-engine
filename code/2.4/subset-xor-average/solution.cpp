/*
Problem: a subset of an array is chosen uniformly at random among all 2^n subsets (the empty one included).
Print twice the expected XOR of the chosen values.
Input: n (1 <= n <= 10^5), then a_1 .. a_n (0 <= a_i < 2^30).
Output: one integer, 2 * E[XOR].
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Twice the expected XOR of a uniformly random subset. A bit that some value has is set in the XOR of exactly half of
// the subsets, so it contributes 2^b / 2 on average; a bit that no value has contributes nothing. Twice the average is the OR.
long long twiceExpectedSubsetXor(const vector<int>& a) {
    long long all = 0;
    for (int x : a) all |= x;  // bit b is set here exactly when some value has bit b
    return all;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << twiceExpectedSubsetXor(a) << "\n";
}
