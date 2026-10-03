/*
Problem: the GCD and the LCM of n positive integers; print -1 for the LCM if it exceeds C.
Input: n C, then a_1 .. a_n (1 <= n <= 10^5, 1 <= a_i, C <= 10^18).
Output: "g L" with L = -1 when the LCM is greater than C.
*/
#include <bits/stdc++.h>
using namespace std;

long long gcdLL(long long a, long long b) {  // Euclid (Theorem 0.4.5); std::gcd does the same
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long C;
    cin >> n >> C;
    long long g = 0, L = 1;  // gcd(0, x) = x, lcm(1, x) = x
    bool tooBig = false;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        g = gcdLL(g, a);
        if (!tooBig) {
            long long q = L / gcdLL(L, a);  // lcm(L, a) = q * a (Theorem 0.4.6)
            if (q > C / a) tooBig = true;   // q * a > C, tested without computing q * a
            else L = q * a;
        }
    }
    cout << g << " " << (tooBig ? -1 : L) << "\n";
}
