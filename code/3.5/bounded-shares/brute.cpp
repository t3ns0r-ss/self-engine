// Brute force: try every share for every person by recursion.
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> lo, hi;

long long share(int i, int left) {
    if (i == n) return left == 0 ? 1 : 0;
    long long ways = 0;
    for (int t = lo[i]; t <= hi[i] && t <= left; t++) ways += share(i + 1, left - t);
    return ways;
}

int main() {
    int k;
    cin >> n >> k;
    lo.resize(n);
    hi.resize(n);
    for (int i = 0; i < n; i++) cin >> lo[i] >> hi[i];
    cout << share(0, k) % 1'000'000'007 << "\n";
}
