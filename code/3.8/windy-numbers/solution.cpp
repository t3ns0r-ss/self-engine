/*
Problem: count the integers x with A <= x <= B in which every two neighbouring digits differ by at least 2
(one-digit numbers, including 0, qualify).
Input: A B (0 <= A <= B <= 10^18).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

string digits;
long long memo[20][11][2];
bool seen[20][11][2];

// prev = previous digit of the number (10 before the first one); started = a non-zero digit has appeared
long long go(int pos, int prev, bool tight, bool started) {
    if (pos == (int)digits.size()) return 1;          // every completed string is valid by construction
    if (!tight && seen[pos][prev][started]) return memo[pos][prev][started];
    int hi = tight ? digits[pos] - '0' : 9;
    long long total = 0;
    for (int c = 0; c <= hi; c++) {
        if (!started && c == 0) {                     // still a leading zero: not a digit (Theorem 3.8.3)
            total += go(pos + 1, 10, tight && c == hi, false);
            continue;
        }
        if (prev != 10 && abs(c - prev) < 2) continue;  // the neighbour rule
        total += go(pos + 1, c, tight && c == hi, true);
    }
    if (!tight) seen[pos][prev][started] = true, memo[pos][prev][started] = total;
    return total;
}

long long countUpTo(long long n) {
    if (n < 0) return 0;
    digits = to_string(n);
    memset(seen, 0, sizeof seen);
    return go(0, 10, true, false);                    // the all-zero string is the number 0
}

int main() {
    long long a, b;
    cin >> a >> b;
    cout << countUpTo(b) - countUpTo(a - 1) << "\n";
}
