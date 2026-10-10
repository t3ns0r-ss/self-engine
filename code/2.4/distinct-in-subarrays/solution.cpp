/*
Problem: the sum, over all subarrays, of the number of distinct values in the subarray.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: the exact sum (at most about 1.4*10^15).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.4.3. The sum over all subarrays of the number of distinct values: a at position i counts in the subarrays
// where it is the first copy, l in (prev, i] and r in [i, n - 1]: (i - prev) * (n - i) of them.
long long distinctInSubarrays(const vector<long long>& a) {
    long long n = a.size(), total = 0;
    map<long long, long long> last;  // value -> its previous position (0-based)
    for (long long i = 0; i < n; i++) {
        long long prev = last.count(a[i]) ? last[a[i]] : -1;
        total += (i - prev) * (n - i);
        last[a[i]] = i;
    }
    return total;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << distinctInSubarrays(a) << "\n";
}
