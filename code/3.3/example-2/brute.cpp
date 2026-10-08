// Brute force: every subset of 1..n as a bitmask; count those with half the total, then halve.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long total = 1LL * n * (n + 1) / 2, count = 0;
    for (long long mask = 0; mask < (1LL << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += i + 1;
        if (2 * s == total) count++;
    }
    cout << (count / 2) % 1000000007 << "\n";
}
