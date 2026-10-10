/*
Problem: the sum a + (a + d) + ... + (a + (n - 1) d).
Input: a d n with |a|, |d| <= 10^6 and 1 <= n <= 10^6.
Output: the sum.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.3. a + (a + d) + ... + (a + (n - 1) d). The product is always even: multiply first, then halve.
long long arithSum(long long a, long long d, long long n) { return n * (2 * a + (n - 1) * d) / 2; }
// snippet:end

int main() {
    long long a, d, n;  // the sum reaches about 5*10^17
    cin >> a >> d >> n;
    cout << arithSum(a, d, n) << "\n";
}
