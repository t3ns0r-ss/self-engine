/*
Problem: t test cases. In each, n integers; count the elements strictly greater than the average.
Input: t, then for each test: n, then a_1..a_n (1 <= a_i <= 10^9); the sum of n over all tests is at most 2*10^5.
Output: one line per test.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.3. One test: how many elements are above the average. Everything is created per test.
int countAboveAverage(const vector<long long>& a) {
    long long n = a.size(), sum = 0;
    for (long long x : a) sum += x;
    int count = 0;
    for (long long x : a)
        if (x * n > sum) count++;  // x > sum / n without dividing
    return count;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);  // a fresh vector per test: nothing to clear, nothing left over
        for (auto& x : a) cin >> x;
        cout << countAboveAverage(a) << "\n";
    }
}
