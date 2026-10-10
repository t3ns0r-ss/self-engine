/*
Problem: print the sum of n integers.
Input: n (1 <= n <= 2*10^5), then n integers a_i with |a_i| <= 10^9.
Output: the sum.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.1. The sum is kept in a long long: 2*10^5 values of 10^9 reach 2*10^14.
long long sumAll(const vector<long long>& a) {
    long long sum = 0;
    for (long long x : a) sum += x;
    return sum;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);  // fast input and output (Section 4.5)
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << sumAll(a) << "\n";
}
