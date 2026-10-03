/*
Problem: AtCoder ABC 284 B Multi Test Cases. For each of T tests, count the odd numbers among N given.
Input: T, then for each test: N, then A_1..A_N (T, N <= 100, A_i <= 10^9).
Output: T lines.
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
        int odd = 0;  // reset for every test: declared inside the loop
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (a % 2 == 1) odd++;
        }
        cout << odd << "\n";
    }
}
