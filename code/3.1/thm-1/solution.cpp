#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.1. Backtracking with a feasibility check: extend the partial solution one row at a time, test the new queen
// against the earlier ones, and undo the marks after the call. Returns the number of solutions; calls counts the nodes.
long long queens(int n, long long& calls) {
    vector<bool> col(n, false), diag(2 * n - 1, false), anti(2 * n - 1, false);
    function<long long(int)> rec = [&](int row) -> long long {
        calls++;
        if (row == n) return 1;
        long long ways = 0;
        for (int c = 0; c < n; c++) {
            if (col[c] || diag[row - c + n - 1] || anti[row + c]) continue;  // reads only the queens already placed
            col[c] = diag[row - c + n - 1] = anti[row + c] = true;
            ways += rec(row + 1);
            col[c] = diag[row - c + n - 1] = anti[row + c] = false;
        }
        return ways;
    };
    return rec(0);
}
// snippet:end

int main() {
    for (int n : {4, 8, 10}) {
        long long calls = 0;
        long long ways = queens(n, calls);
        long long unpruned = 0, level = 1;
        for (int i = 0; i <= n; i++) unpruned += level, level *= n;
        cout << n << " queens: " << ways << " solutions, " << calls << " calls instead of " << unpruned << " nodes\n";
    }
    for (int n = 1; n <= 6; n++) {
        long long calls = 0, brute = 0;
        vector<int> c(n, 0);
        for (long long code = 0; code < (long long)pow(n, n) + (n == 0); code++) {
            long long x = code;
            for (int i = 0; i < n; i++) c[i] = x % n, x /= n;
            bool ok = true;
            for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (c[i] == c[j] || abs(c[i] - c[j]) == j - i) ok = false;
            brute += ok;
        }
        if (brute != queens(n, calls)) return 1;
    }
}
