/*
Problem: answer q queries: the XOR of all integers L, L + 1, ..., R.
Input: q (1 <= q <= 2*10^5), then q lines L R (0 <= L <= R <= 10^18).
Output: one line per query.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.1. The XOR of 0, 1, ..., n by the period-4 pattern, and the XOR of L..R: the part 0..L-1 cancels.
long long xorUpTo(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}
long long xorRange(long long L, long long R) { return xorUpTo(R) ^ (L == 0 ? 0 : xorUpTo(L - 1)); }
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long L, R;
        cin >> L >> R;
        cout << xorRange(L, R) << "\n";
    }
}
