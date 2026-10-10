/*
Problem: ABC 318 C Blue Spring. N days with fares F_i; one-day passes come in batches of D for P yen
(leftovers allowed). Print the least total cost.
Input: N D P (1 <= N, D <= 2*10^5, 1 <= P <= 10^9), then F_1 .. F_N (1 <= F_i <= 10^9).
Output: the least total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The cheapest way to cover n days with fares f_i, where p buys a batch of d one-day passes: the most expensive days are
// covered by passes first, block by block of d days.
long long cheapestTrip(vector<long long> f, int d, long long p) {
    sort(f.rbegin(), f.rend());  // passes go to the most expensive days first
    int n = f.size();
    long long total = 0;  // up to 2*10^5 * 10^9 = 2*10^14
    for (int start = 0; start < n; start += d) {
        long long block = 0;  // the next block of up to d days
        for (int i = start; i < min(n, start + d); i++) block += f[i];
        total += min(block, p);  // one batch of passes, or pay the fares of this block
    }
    return total;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    long long p;
    cin >> n >> d >> p;
    vector<long long> f(n);
    for (auto& x : f) cin >> x;
    cout << cheapestTrip(f, d, p) << "\n";
}
