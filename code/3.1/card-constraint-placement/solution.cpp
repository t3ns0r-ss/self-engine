#include <bits/stdc++.h>
using namespace std;

long long queens(int n) {
    vector<bool> col(n, false), diag(2 * n - 1, false), anti(2 * n - 1, false);
    function<long long(int)> rec = [&](int row) -> long long {
        if (row == n) return 1;
        long long ways = 0;
        for (int c = 0; c < n; c++) {
            if (col[c] || diag[row - c + n - 1] || anti[row + c]) continue;
            col[c] = diag[row - c + n - 1] = anti[row + c] = true;
            ways += rec(row + 1);
            col[c] = diag[row - c + n - 1] = anti[row + c] = false;
        }
        return ways;
    };
    return rec(0);
}
int main() {
    // P1: the ways to place 4 non-attacking queens on a 4 x 4 board. Brute: all 4^4 column choices. Method: backtracking.
    int brute = 0;
    for (int code = 0; code < 256; code++) {
        int c[4];
        for (int i = 0; i < 4; i++) c[i] = code >> (2 * i) & 3;
        bool ok = true;
        for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) if (c[i] == c[j] || abs(c[i] - c[j]) == j - i) ok = false;
        brute += ok;
    }
    cout << "P1 brute=" << brute << " method=" << queens(4) << '\n';
    // N1: the ways to place 14 non-attacking rooks on a 14 x 14 board, found by listing placements: 14! leaves.
    long long fact = 1;
    for (int i = 2; i <= 14; i++) fact *= i;
    cout << "N1 brute=" << fact << " method=" << (fact > 1000000000LL ? "too-slow" : "ok") << '\n';
}
