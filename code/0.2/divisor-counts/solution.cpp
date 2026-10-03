/*
Problem: for every k from 1 to n, let d(k) be its number of divisors. Print the sum of d(k)
and the largest d(k).
Input: n (1 <= n <= 10^7).
Output: two numbers.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1, 0);  // cnt[k] = d(k)
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)  // the multiples of i: about n / i of them (Theorem 0.2.5)
            cnt[j]++;                    // i divides j
    long long total = 0;  // about n ln n, up to 1.6*10^8 for n = 10^7
    int best = 0;
    for (int k = 1; k <= n; k++) {
        total += cnt[k];
        best = max(best, cnt[k]);
    }
    cout << total << " " << best << "\n";
}
