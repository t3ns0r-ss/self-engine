/*
Problem: AtCoder ABC 174 C Repsept. The first term of 7, 77, 777, ... that is a multiple of K.
Input: K (1 <= K <= 10^6).
Output: its position, or -1 if no term is a multiple of K.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The position of the first of 7, 77, 777, ... that is a multiple of k, or -1. Only the remainder is kept.
long long repsept(long long k) {
    long long r = 0;
    for (long long i = 1; i <= k; i++) {
        r = (r * 10 + 7) % k;  // next term = 10 * term + 7
        if (r == 0) return i;
    }
    return -1;  // k remainders without 0: they already repeat
}
// snippet:end

int main() {
    long long k;
    cin >> k;
    cout << repsept(k) << "\n";
}
