/*
Problem: count the integers x with A <= x <= B that use at most K different digits (0 counts as using the digit 0).
Input: A B K (0 <= A <= B <= 10^18, 1 <= K <= 10).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 3.8.1 and 3.8.3. The integers in [A, B] that use at most K different digits: the state is the mask of digits used, a
// started flag stops leading zeros from counting as digits, and F(B) - F(A - 1) gives the range.
long long fewDistinct(long long A, long long B, int K) {
    auto countUpTo = [&](long long n) -> long long {
        if (n < 0) return 0;
        string digits = to_string(n);
        int L = digits.size();
        vector<vector<array<long long, 2>>> memo(L + 1, vector<array<long long, 2>>(1 << 10, {-1, -1}));
        function<long long(int, int, bool, bool)> go = [&](int pos, int used, bool tight, bool started) -> long long {
            if (pos == L) return __builtin_popcount(started ? used : 1) <= K;  // 0 itself uses {0}
            if (!tight && memo[pos][used][started] != -1) return memo[pos][used][started];
            int hi = tight ? digits[pos] - '0' : 9;
            long long total = 0;
            for (int c = 0; c <= hi; c++) {
                bool nowStarted = started || c != 0;
                int nowUsed = nowStarted ? (used | 1 << c) : used;
                if (__builtin_popcount(nowUsed) > K) continue;
                total += go(pos + 1, nowUsed, tight && c == hi, nowStarted);
            }
            if (!tight) memo[pos][used][started] = total;
            return total;
        };
        return go(0, 0, true, false);
    };
    return countUpTo(B) - countUpTo(A - 1);
}
// snippet:end

int main() {
    long long a, b;
    int k;
    cin >> a >> b >> k;
    cout << fewDistinct(a, b, k) << "\n";
}
