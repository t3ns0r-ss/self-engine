/*
Problem: count the integers x with A <= x <= B in which every two neighbouring digits differ by at least 2
(one-digit numbers, including 0, qualify).
Input: A B (0 <= A <= B <= 10^18).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.3. The integers in [A, B] in which every two neighbouring digits differ by at least 2: the state is the previous digit
// (10 before the first one) and the started flag.
long long windy(long long A, long long B) {
    auto countUpTo = [&](long long n) -> long long {
        if (n < 0) return 0;
        string digits = to_string(n);
        int L = digits.size();
        vector<vector<array<long long, 2>>> memo(L + 1, vector<array<long long, 2>>(11, {-1, -1}));
        function<long long(int, int, bool, bool)> go = [&](int pos, int prev, bool tight, bool started) -> long long {
            if (pos == L) return 1;
            if (!tight && memo[pos][prev][started] != -1) return memo[pos][prev][started];
            int hi = tight ? digits[pos] - '0' : 9;
            long long total = 0;
            for (int c = 0; c <= hi; c++) {
                if (!started && c == 0) { total += go(pos + 1, 10, tight && c == hi, false); continue; }  // a leading zero
                if (prev != 10 && abs(c - prev) < 2) continue;  // the neighbour rule
                total += go(pos + 1, c, tight && c == hi, true);
            }
            if (!tight) memo[pos][prev][started] = total;
            return total;
        };
        return go(0, 10, true, false);
    };
    return countUpTo(B) - countUpTo(A - 1);
}
// snippet:end

int main() {
    long long a, b;
    cin >> a >> b;
    cout << windy(a, b) << "\n";
}
