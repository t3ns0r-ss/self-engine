/*
Problem: product of n non-negative integers, or -1 if it exceeds 10^18.
Input: n (1 <= n <= 10^5), then n integers 0 <= a_i <= 10^18.
Output: the product, or -1 if it is greater than 10^18.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);  // values up to 10^18 need 64 bits
    for (auto& x : a) cin >> x;

    for (long long x : a) {
        if (x == 0) {  // a zero makes the product 0, whatever comes before it
            cout << 0 << "\n";
            return 0;
        }
    }
    const long long LIMIT = 1000000000000000000LL;  // 10^18
    long long prod = 1;
    for (long long x : a) {
        if (prod > LIMIT / x) {  // prod * x > LIMIT (Theorem 0.1.2), checked without overflow
            cout << -1 << "\n";
            return 0;
        }
        prod *= x;
    }
    cout << prod << "\n";
}
