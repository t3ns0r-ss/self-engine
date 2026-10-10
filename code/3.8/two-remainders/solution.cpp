/*
Problem: count the integers x with A <= x <= B such that x is divisible by M and its digit sum is divisible by D.
Input: A B M D (0 <= A <= B <= 10^18, 1 <= M, D <= 30).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.1 with two remainders as the state: rv = the value mod M so far, rs = the digit sum mod D so far. Leading zeros
// change neither, so no started flag is needed.
long long twoRemainders(long long A, long long B, int M, int D) {
    auto countUpTo = [&](long long n) -> long long {
        if (n < 0) return 0;
        string digits = to_string(n);
        int L = digits.size();
        vector<vector<vector<long long>>> memo(L + 1, vector<vector<long long>>(M, vector<long long>(D, -1)));
        function<long long(int, int, int, bool)> go = [&](int pos, int rv, int rs, bool tight) -> long long {
            if (pos == L) return rv == 0 && rs == 0;
            if (!tight && memo[pos][rv][rs] != -1) return memo[pos][rv][rs];
            int hi = tight ? digits[pos] - '0' : 9;
            long long total = 0;
            for (int c = 0; c <= hi; c++) total += go(pos + 1, (rv * 10 + c) % M, (rs + c) % D, tight && c == hi);
            if (!tight) memo[pos][rv][rs] = total;
            return total;
        };
        return go(0, 0, 0, true);
    };
    return countUpTo(B) - countUpTo(A - 1);
}
// snippet:end

int main() {
    long long a, b;
    int m, d;
    cin >> a >> b >> m >> d;
    cout << twoRemainders(a, b, m, d) << "\n";
}
