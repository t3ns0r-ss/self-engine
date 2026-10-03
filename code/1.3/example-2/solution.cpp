/*
Problem: AtCoder ABC 130 D Enough Array. Count the contiguous subarrays with sum at least K.
Input: N K, then N positive integers (N <= 10^5, a_i <= 10^5, K <= 10^10).
Output: the number of such subarrays.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;  // up to 10^10, beyond int
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // Count the windows with sum < K (closed under shrinking), then take the rest.
    long long below = 0;  // up to n(n+1)/2, about 5*10^9
    long long sum = 0;    // sum of a[l..r]
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= K) {  // window reaches K: not in the "below" family
            sum -= a[l];
            l++;
        }
        below += r - l + 1;  // windows [l..r], ..., [r..r] all have sum < K
    }
    long long total = (long long)n * (n + 1) / 2;
    cout << total - below << "\n";
}
