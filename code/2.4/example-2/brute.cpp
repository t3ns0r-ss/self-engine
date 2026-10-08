#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int n, m, k;
    cin >> n >> m >> k;
    int cells = n * m;
    long long total = 0;
    for (int mask = 0; mask < (1 << cells); mask++) {  // every set of cells (topic 0.5)
        if (__builtin_popcount(mask) != k) continue;
        for (int a = 0; a < cells; a++)
            for (int b = a + 1; b < cells; b++)
                if ((mask >> a & 1) && (mask >> b & 1)) total += abs(a / m - b / m) + abs(a % m - b % m);
    }
    cout << total % MOD << "\n";
}
