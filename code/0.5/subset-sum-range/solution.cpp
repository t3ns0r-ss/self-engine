/*
Problem: count the subsets (including the empty one) of n values whose sum lies in [L, R].
Input: n L R, then a_0 .. a_{n-1} (1 <= n <= 20, 0 <= a_i <= 10^9, 0 <= L <= R <= 2*10^10).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long lo, hi;
    cin >> n >> lo >> hi;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {  // every subset once (Theorem 0.5.2)
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) sum += a[i];  // item i is in the subset
        if (lo <= sum && sum <= hi) count++;
    }
    cout << count << "\n";
}
