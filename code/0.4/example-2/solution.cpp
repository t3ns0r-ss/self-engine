/*
Problem: AtCoder ABC 174 C Repsept. The first term of 7, 77, 777, ... that is a multiple of K.
Input: K (1 <= K <= 10^6).
Output: its position, or -1 if no term is a multiple of K.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    cin >> k;
    long long r = 0;  // the remainder of the current term modulo k, never the term itself
    for (long long i = 1; i <= k; i++) {
        r = (r * 10 + 7) % k;  // next term = 10 * term + 7 (Theorem 0.4.4)
        if (r == 0) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";  // k remainders without 0: they already repeat (Theorem 0.3.1)
}
