#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.2. Pascal's rule: C(n, r) = C(n-1, r-1) + C(n-1, r) builds the whole triangle in O(n^2).
vector<vector<long long>> pascal(int n) {
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + (j <= i - 1 ? C[i - 1][j] : 0);
    }
    return C;
}
// snippet:end

int main() {
    auto C = pascal(10);
    cout << "C(6, 3) = " << C[6][3] << " = C(5, 2) + C(5, 3) = " << C[5][2] << " + " << C[5][3] << '\n';
    cout << "row 5:";
    for (int j = 0; j <= 5; j++) cout << ' ' << C[5][j];
    cout << " (sum " << accumulate(C[5].begin(), C[5].begin() + 6, 0LL) << " = 2^5)\n";
    for (int n = 0; n <= 10; n++) {
        long long sum = 0;
        for (int r = 0; r <= n; r++) {
            sum += C[n][r];
            if (C[n][r] != C[n][n - r]) return 1;
            long long f = 1;  // n! / (r! (n-r)!) by the product formula
            for (int i = 0; i < r; i++) f = f * (n - i) / (i + 1);
            if (f != C[n][r]) return 1;
        }
        if (sum != (1LL << n)) return 1;
    }
}
