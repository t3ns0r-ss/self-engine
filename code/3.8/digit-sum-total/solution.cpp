/*
Problem: the sum of the digit sums of all integers x with A <= x <= B, modulo 10^9 + 7.
Input: A B (0 <= A <= B <= 10^18).
Output: the sum modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 3.8.4 and 3.8.2. Each state returns (count, total of digit sums) of the completions; digit c adds c to each of the n
// completions. Only states with tight == false are stored.
long long digitSumTotal(long long A, long long B) {
    const long long MOD = 1'000'000'007;
    auto sumUpTo = [&](long long n) -> long long {
        if (n < 0) return 0;
        string digits = to_string(n);
        vector<pair<long long, long long>> memo(digits.size() + 1);
        vector<bool> seen(digits.size() + 1, false);
        function<pair<long long, long long>(int, bool)> go = [&](int pos, bool tight) -> pair<long long, long long> {
            if (pos == (int)digits.size()) return {1, 0};
            if (!tight && seen[pos]) return memo[pos];
            int hi = tight ? digits[pos] - '0' : 9;
            long long count = 0, total = 0;
            for (int c = 0; c <= hi; c++) {
                auto [n2, t] = go(pos + 1, tight && c == hi);
                count = (count + n2) % MOD;
                total = (total + t + c * n2) % MOD;
            }
            if (!tight) seen[pos] = true, memo[pos] = {count, total};
            return {count, total};
        };
        return go(0, true).second;
    };
    return (sumUpTo(B) - sumUpTo(A - 1) + MOD) % MOD;
}
// snippet:end

int main() {
    long long a, b;
    cin >> a >> b;
    cout << digitSumTotal(a, b) << "\n";
}
