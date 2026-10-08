/*
Problem: CSES 1145, Increasing Subsequence. The length of the longest strictly increasing subsequence.
Input: n (n <= 2 * 10^5), then n integers x_i (1 <= x_i <= 10^9).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> tails;  // tails[k] = smallest last value of an increasing subsequence of length k + 1 (Theorem 3.4.2)
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = lower_bound(tails.begin(), tails.end(), x);  // strictly increasing: first tail >= x
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << tails.size() << "\n";
}
