/*
Problem: LeetCode 233 Number of Digit One, as a program. Count all the digits 1 written in the integers 0..n.
Input: n (0 <= n <= 10^9).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

string digits;
pair<long long, long long> memo[11];  // (count, ones) of the free completions from a position
bool seen[11];

// returns (number of completions, total number of digit 1 in them) (Theorem 3.8.4)
pair<long long, long long> go(int pos, bool tight) {
    if (pos == (int)digits.size()) return {1, 0};
    if (!tight && seen[pos]) return memo[pos];
    int hi = tight ? digits[pos] - '0' : 9;
    long long count = 0, ones = 0;
    for (int c = 0; c <= hi; c++) {
        auto [n, t] = go(pos + 1, tight && c == hi);
        count += n;
        ones += t + (c == 1 ? n : 0);  // a 1 here appears once in each of the n completions
    }
    if (!tight) seen[pos] = true, memo[pos] = {count, ones};
    return {count, ones};
}

int main() {
    long long n;
    cin >> n;
    digits = to_string(n);
    cout << go(0, true).second << "\n";
}
