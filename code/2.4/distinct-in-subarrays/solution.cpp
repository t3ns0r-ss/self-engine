/*
Problem: the sum, over all subarrays, of the number of distinct values in the subarray.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the exact sum (at most about 1.4*10^15).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    map<long long, long long> last;  // value -> its previous position (0-based), or -1
    long long total = 0;
    for (long long i = 0; i < n; i++) {
        long long a;
        cin >> a;
        long long prev = last.count(a) ? last[a] : -1;
        // a at position i counts in subarrays [l, r] where it is the first copy of a:
        // l in (prev, i], r in [i, n - 1]  (Theorem 2.4.3)
        total += (i - prev) * (n - i);
        last[a] = i;
    }
    cout << total << "\n";
}
