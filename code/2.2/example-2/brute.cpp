#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int n;
    cin >> n;
    long long N = 1;
    for (int i = 0; i < n; i++) {
        long long x, k;
        cin >> x >> k;
        for (long long j = 0; j < k; j++) N *= x;
    }
    long long cnt = 0, sum = 0, prod = 1;
    for (long long d = 1; d <= N; d++)
        if (N % d == 0) cnt++, sum = (sum + d) % MOD, prod = prod * (d % MOD) % MOD;
    cout << cnt % MOD << " " << sum << " " << prod << "\n";
}
