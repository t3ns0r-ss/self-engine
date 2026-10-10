/*
Problem: AtCoder ABC 284 B Multi Test Cases. For each of T tests, count the odd numbers among N given.
Input: T, then for each test: N, then A_1..A_N (T, N <= 100, A_i <= 10^9).
Output: T lines.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// One test: how many of the numbers are odd. The counter is created per call, so it is reset for every test.
int countOdd(const vector<int>& a) {
    int odd = 0;
    for (int x : a)
        if (x % 2 == 1) odd++;
    return odd;
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
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << countOdd(a) << "\n";
    }
}
