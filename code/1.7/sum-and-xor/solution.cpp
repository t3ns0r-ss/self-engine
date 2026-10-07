/*
Problem: for each test, find a, b >= 0 with a + b = s and a XOR b = x, with a as small as possible;
print -1 if there are none.
Input: t (1 <= t <= 10^5), then t lines s x (0 <= s, x <= 10^18).
Output: one line per test: a b, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long s, x;
        cin >> s >> x;
        // a + b = (a xor b) + 2 (a and b), so the common bits are c = (s - x) / 2 (Theorem 1.7.5)
        if (s < x || (s - x) % 2 != 0) {
            cout << -1 << "\n";
            continue;
        }
        long long c = (s - x) / 2;
        if (c & x) {  // a bit cannot be in both and in exactly one
            cout << -1 << "\n";
            continue;
        }
        // a must contain c; giving every bit of x to b makes a smallest
        cout << c << " " << (c | x) << "\n";
    }
}
