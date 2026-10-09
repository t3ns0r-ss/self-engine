/*
Problem: count the integers x with A <= x <= B that use at most K different digits (0 counts as using the digit 0).
Input: A B K (0 <= A <= B <= 10^18, 1 <= K <= 10).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

string digits;              // the decimal digits of the current bound N
int K;
long long memo[20][1 << 10][2];
bool seen[20][1 << 10][2];

// completions of positions pos.. with `used` digits so far; only states with tight == false are stored
long long go(int pos, int used, bool tight, bool started) {
    if (pos == (int)digits.size()) return __builtin_popcount(started ? used : 1) <= K;  // 0 itself uses {0}
    if (!tight && seen[pos][used][started]) return memo[pos][used][started];
    int hi = tight ? digits[pos] - '0' : 9;
    long long total = 0;
    for (int c = 0; c <= hi; c++) {
        bool nowStarted = started || c != 0;          // leading zeros are not digits (Theorem 3.8.3)
        int nowUsed = nowStarted ? (used | 1 << c) : used;
        if (__builtin_popcount(nowUsed) > K) continue;  // already too many: no completion works
        total += go(pos + 1, nowUsed, tight && c == hi, nowStarted);
    }
    if (!tight) seen[pos][used][started] = true, memo[pos][used][started] = total;
    return total;
}

// F(N) = how many x in [0, N] qualify (Theorem 3.8.1)
long long countUpTo(long long n) {
    if (n < 0) return 0;
    digits = to_string(n);
    memset(seen, 0, sizeof seen);                    // the memo depends on the length of N
    return go(0, 0, true, false);
}

int main() {
    long long a, b;
    cin >> a >> b >> K;
    cout << countUpTo(b) - countUpTo(a - 1) << "\n";  // Theorem 3.8.2
}
