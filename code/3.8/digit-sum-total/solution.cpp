/*
Problem: the sum of the digit sums of all integers x with A <= x <= B, modulo 10^9 + 7.
Input: A B (0 <= A <= B <= 10^18).
Output: the sum modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;
string digits;
pair<long long, long long> memo[20];   // (count, total of digit sums) of the completions; only for tight == false
bool seen[20];

pair<long long, long long> go(int pos, bool tight) {
    if (pos == (int)digits.size()) return {1, 0};     // one completion (the empty one), digit sum 0
    if (!tight && seen[pos]) return memo[pos];
    int hi = tight ? digits[pos] - '0' : 9;
    long long count = 0, total = 0;
    for (int c = 0; c <= hi; c++) {
        auto [n, t] = go(pos + 1, tight && c == hi);
        count = (count + n) % MOD;
        total = (total + t + c * n) % MOD;            // digit c adds c to each of the n completions (Theorem 3.8.4)
    }
    if (!tight) seen[pos] = true, memo[pos] = {count, total};
    return {count, total};
}

long long sumUpTo(long long n) {
    if (n < 0) return 0;
    digits = to_string(n);
    memset(seen, 0, sizeof seen);
    return go(0, true).second;
}

int main() {
    long long a, b;
    cin >> a >> b;
    cout << (sumUpTo(b) - sumUpTo(a - 1) + MOD) % MOD << "\n";  // Theorem 3.8.2 modulo a prime
}
