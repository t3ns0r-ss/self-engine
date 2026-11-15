/*
Problem: CSES 1145, Increasing Subsequence. The length of the longest strictly increasing subsequence.
Input: n (n <= 2 * 10^5), then n integers x_i (1 <= x_i <= 10^9).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1145. The longest strictly increasing subsequence with the tails array.
int increasingSubsequence(const vector<int>& x) {
    vector<int> tails;  // tails[k] = smallest last value of an increasing subsequence of length k + 1
    for (int v : x) {
        auto it = lower_bound(tails.begin(), tails.end(), v);  // strictly increasing: first tail >= v
        if (it == tails.end()) tails.push_back(v);
        else *it = v;
    }
    return tails.size();
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int& v : x) cin >> v;
    cout << increasingSubsequence(x) << "\n";
}
