/*
Problem: t test cases. In each, n integers; count the elements strictly greater than the average.
Input: t, then for each test: n, then a_1..a_n (1 <= a_i <= 10^9); the sum of n over all tests is at most 2*10^5.
Output: one line per test.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);  // a fresh vector per test: nothing to clear, nothing left over
        long long sum = 0;       // up to 2*10^14
        for (auto& x : a) {
            cin >> x;
            sum += x;
        }
        int count = 0;
        for (long long x : a)
            if (x * n > sum) count++;  // x > sum / n without division; x * n <= 2*10^14
        cout << count << "\n";
    }
}
