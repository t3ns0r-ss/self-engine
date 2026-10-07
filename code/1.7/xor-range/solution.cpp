/*
Problem: answer q queries: the XOR of all integers L, L + 1, ..., R.
Input: q (1 <= q <= 2*10^5), then q lines L R (0 <= L <= R <= 10^18).
Output: one line per query.
*/
#include <bits/stdc++.h>
using namespace std;

// XOR of 0, 1, ..., n (n >= 0), by the period-4 pattern of Section 4.1
long long xorUpTo(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long L, R;
        cin >> L >> R;
        // 0..R = (0..L-1) followed by (L..R); the first part cancels (Theorem 1.7.1)
        long long below = L == 0 ? 0 : xorUpTo(L - 1);
        cout << (xorUpTo(R) ^ below) << "\n";
    }
}
