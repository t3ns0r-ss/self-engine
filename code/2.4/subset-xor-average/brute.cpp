#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;  // the sum of the XOR over all 2^n subsets
    for (int mask = 0; mask < (1 << n); mask++) {
        long long x = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) x ^= a[i];
        total += x;
    }
    // twice the average is 2 * total / 2^n, which is an integer
    cout << (2 * total) / (1LL << n) << "\n";
}
