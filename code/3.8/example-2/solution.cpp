/*
Problem: LeetCode 233 Number of Digit One, as a program. Count all the digits 1 written in the integers 0..n.
Input: n (0 <= n <= 10^9).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// LeetCode 233. Each state returns (number of completions, total number of digit 1 in them); a 1 here appears once in each of the
// n completions.
long long digitOnes(long long n) {
    string digits = to_string(n);
    vector<pair<long long, long long>> memo(digits.size() + 1);
    vector<bool> seen(digits.size() + 1, false);
    function<pair<long long, long long>(int, bool)> go = [&](int pos, bool tight) -> pair<long long, long long> {
        if (pos == (int)digits.size()) return {1, 0};
        if (!tight && seen[pos]) return memo[pos];
        int hi = tight ? digits[pos] - '0' : 9;
        long long count = 0, ones = 0;
        for (int c = 0; c <= hi; c++) {
            auto [n2, t] = go(pos + 1, tight && c == hi);
            count += n2;
            ones += t + (c == 1 ? n2 : 0);
        }
        if (!tight) seen[pos] = true, memo[pos] = {count, ones};
        return {count, ones};
    };
    return go(0, true).second;
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    cout << digitOnes(n) << "\n";
}
