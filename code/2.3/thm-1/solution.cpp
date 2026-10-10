#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.1. Product rule: strings of length k over m symbols with no two equal neighbours, m * (m-1)^(k-1);
// and the sum rule over disjoint cases. Also n! orders and n!/(n-r)! ordered selections.
long long noEqualNeighbours(int m, int k) {
    long long ways = m;                    // the first symbol: m options
    for (int i = 1; i < k; i++) ways *= m - 1;  // every later symbol: m - 1 options, whatever came before
    return ways;
}
long long ordered(int n, int r) {
    long long ways = 1;
    for (int i = 0; i < r; i++) ways *= n - i;
    return ways;
}
// snippet:end

int main() {
    cout << "strings of length 3 over {a, b, c} with no equal neighbours: " << noEqualNeighbours(3, 3) << '\n';
    cout << "all strings of length 3 over 3 symbols: " << 27 << ", orders of 4 elements: " << ordered(4, 4) << ", ordered selections of 3 from 5: " << ordered(5, 3) << '\n';
    for (int m = 1; m <= 4; m++) for (int k = 1; k <= 5; k++) {
        long long brute = 0;
        long long total = 1;
        for (int i = 0; i < k; i++) total *= m;
        for (long long code = 0; code < total; code++) {
            long long c = code;
            int prev = -1;
            bool ok = true;
            for (int i = 0; i < k; i++) { int d = c % m; c /= m; if (d == prev) ok = false; prev = d; }
            brute += ok;
        }
        if (brute != noEqualNeighbours(m, k)) return 1;
    }
}
