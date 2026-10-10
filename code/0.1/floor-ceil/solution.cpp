/*
Problem: for each query (a, b), print floor(a / b) and ceil(a / b).
Input: q, then q lines "a b" with |a|, |b| <= 10^18 and b != 0.
Output: one line per query: the floor and the ceiling.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.4. floor(a / b) for b != 0.
long long floorDiv(long long a, long long b) {
    if (b < 0) a = -a, b = -b;     // a / b == (-a) / (-b), and now the divisor is positive
    long long q = a / b;           // truncated toward zero
    if (a % b != 0 && a < 0) q--;  // a negative non-multiple was rounded up: go one lower
    return q;
}

// ceil(a / b) = -floor(-a / b)
long long ceilDiv(long long a, long long b) { return -floorDiv(-a, b); }
// snippet:end

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long a, b;
        cin >> a >> b;
        cout << floorDiv(a, b) << " " << ceilDiv(a, b) << "\n";
    }
}
