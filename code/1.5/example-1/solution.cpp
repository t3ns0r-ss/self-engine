/*
Problem: ABC 318 C Blue Spring. N days with fares F_i; one-day passes come in batches of D for P yen
(leftovers allowed). Print the least total cost.
Input: N D P (1 <= N, D <= 2*10^5, 1 <= P <= 10^9), then F_1 .. F_N (1 <= F_i <= 10^9).
Output: the least total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    long long p;
    cin >> n >> d >> p;
    vector<long long> f(n);
    for (auto& x : f) cin >> x;
    sort(f.rbegin(), f.rend());  // passes go to the most expensive days first
    long long total = 0;         // up to 2*10^5 * 10^9 = 2*10^14
    for (int start = 0; start < n; start += d) {
        // the next block of up to d days, the most expensive not yet decided
        long long block = 0;
        for (int i = start; i < min(n, start + d); i++) block += f[i];
        total += min(block, p);  // one batch of passes, or pay the fares of this block
    }
    cout << total << "\n";
}
