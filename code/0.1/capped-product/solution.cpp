/*
Problem: product of n non-negative integers, or -1 if it exceeds 10^18.
Input: n (1 <= n <= 10^5), then n integers 0 <= a_i <= 10^18.
Output: the product, or -1 if it is greater than 10^18.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.2. The product of a, or -1 if it exceeds 10^18. The product never leaves the 64-bit range.
long long cappedProduct(const vector<long long>& a) {
    const long long LIMIT = 1000000000000000000LL;  // 10^18
    for (long long x : a)
        if (x == 0) return 0;  // a zero makes the product 0, whatever comes before it
    long long prod = 1;
    for (long long x : a) {
        if (prod > LIMIT / x) return -1;  // prod * x > LIMIT, checked without overflow
        prod *= x;
    }
    return prod;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << cappedProduct(a) << "\n";
}
