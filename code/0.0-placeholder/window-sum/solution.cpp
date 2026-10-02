#include <bits/stdc++.h>
using namespace std;

/*
Problem: longest contiguous segment with sum at most K.
Input: n K, then n positive integers.
Output: the maximum length.
*/
int main() {
    int n;
    long long k;  // sums can reach 2·10^14, beyond int
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long sum = 0;
    int best = 0, l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > k) sum -= a[l++];
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
