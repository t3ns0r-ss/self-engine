/*
Problem: AtCoder ABC 130 D Enough Array. Count the contiguous subarrays with sum at least K.
Input: N K, then N positive integers (N <= 10^5, a_i <= 10^5, K <= 10^10).
Output: the number of such subarrays.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The number of subarrays with sum at least K (positive values): all subarrays minus those with sum < K,
// which are counted with a shrinkable window.
long long countAtLeast(const vector<long long>& a, long long K) {
    int n = a.size(), l = 0;
    long long below = 0, sum = 0;  // sum of a[l..r]
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= K) {  // window reaches K: not in the "below" family
            sum -= a[l];
            l++;
        }
        below += r - l + 1;  // windows [l..r], ..., [r..r] all have sum < K
    }
    return (long long)n * (n + 1) / 2 - below;
}
// snippet:end

int main() {
    int n;
    long long K;  // up to 10^10, beyond int
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << countAtLeast(a, K) << "\n";
}
