/*
Problem: print all divisors of N in increasing order.
Input: N (1 <= N <= 10^12).
Output: the divisors, separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.2. All divisors of n in increasing order; d is tried only up to sqrt(n), at most 10^6 values for n <= 10^12.
vector<long long> divisors(long long n) {
    vector<long long> small, large;  // d <= sqrt(n), and their partners n / d
    for (long long d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d != n / d) large.push_back(n / d);  // a square root is recorded once
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    for (long long d : divisors(n)) cout << d << " ";
    cout << "\n";
}
