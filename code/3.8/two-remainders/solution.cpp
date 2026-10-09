/*
Problem: count the integers x with A <= x <= B such that x is divisible by M and its digit sum is divisible by D.
Input: A B M D (0 <= A <= B <= 10^18, 1 <= M, D <= 30).
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

string digits;
int M, D;
long long memo[20][30][30];
bool seen[20][30][30];

// rv = value mod M so far, rs = digit sum mod D so far (Theorem 3.8.1 with two remainders as the state)
long long go(int pos, int rv, int rs, bool tight) {
    if (pos == (int)digits.size()) return rv == 0 && rs == 0;
    if (!tight && seen[pos][rv][rs]) return memo[pos][rv][rs];
    int hi = tight ? digits[pos] - '0' : 9;
    long long total = 0;
    for (int c = 0; c <= hi; c++)
        total += go(pos + 1, (rv * 10 + c) % M, (rs + c) % D, tight && c == hi);
    if (!tight) seen[pos][rv][rs] = true, memo[pos][rv][rs] = total;
    return total;
}

long long countUpTo(long long n) {
    if (n < 0) return 0;
    digits = to_string(n);
    memset(seen, 0, sizeof seen);
    return go(0, 0, 0, true);  // leading zeros change neither remainder, so no started flag is needed
}

int main() {
    long long a, b;
    cin >> a >> b >> M >> D;
    cout << countUpTo(b) - countUpTo(a - 1) << "\n";
}
