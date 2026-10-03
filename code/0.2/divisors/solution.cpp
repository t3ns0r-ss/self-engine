/*
Problem: print all divisors of N in increasing order.
Input: N (1 <= N <= 10^12).
Output: the divisors, separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;  // up to 10^12
    cin >> n;
    vector<long long> small, large;  // d <= sqrt(n), and their partners n / d
    for (long long d = 1; d * d <= n; d++) {  // at most 10^6 values (Theorem 0.2.2)
        if (n % d == 0) {
            small.push_back(d);
            if (d != n / d) large.push_back(n / d);  // a square root is recorded once
        }
    }
    // small is increasing, large is decreasing: print small, then large backwards
    for (long long d : small) cout << d << " ";
    for (int i = (int)large.size() - 1; i >= 0; i--) cout << large[i] << " ";
    cout << "\n";
}
