#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    vector<vector<long long>> C(201, vector<long long>(201, 0));  // Pascal's rule
    for (int n = 0; n <= 200; n++) {
        C[n][0] = 1;
        for (int r = 1; r <= n; r++) C[n][r] = (C[n - 1][r - 1] + C[n - 1][r]) % MOD;
    }
    int q;
    cin >> q;
    while (q--) {
        int n, r;
        cin >> n >> r;
        cout << (r > n ? 0 : C[n][r]) << "\n";
    }
}
