/*
Problem: for each test, find a, b >= 0 with a + b = s and a XOR b = x, with a as small as possible;
print -1 if there are none.
Input: t (1 <= t <= 10^5), then t lines s x (0 <= s, x <= 10^18).
Output: one line per test: a b, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.5. The pair (a, b) with a + b = s and a xor b = x and the smallest a, or {-1, -1} if there is none:
// a + b = (a xor b) + 2 (a and b), so the common bits are c = (s - x) / 2.
pair<long long, long long> splitSumXor(long long s, long long x) {
    if (s < x || (s - x) % 2 != 0) return {-1, -1};
    long long c = (s - x) / 2;
    if (c & x) return {-1, -1};  // a bit cannot be in both and in exactly one
    return {c, c | x};           // a contains c; giving every bit of x to b makes a smallest
}
// snippet:end

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long s, x;
        cin >> s >> x;
        pair<long long, long long> r = splitSumXor(s, x);
        if (r.first < 0) cout << -1 << "\n";
        else cout << r.first << " " << r.second << "\n";
    }
}
