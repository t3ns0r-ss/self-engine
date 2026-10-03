/*
Problem: print the sum of n integers.
Input: n (1 <= n <= 2*10^5), then n integers a_i with |a_i| <= 10^9.
Output: the sum.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);  // fast input and output (Section 4.5)
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long sum = 0;  // up to 2*10^5 * 10^9 = 2*10^14, beyond int
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        sum += x;
    }
    cout << sum << "\n";
}
