/*
Problem: the GCD and the LCM of n positive integers; print -1 for the LCM if it exceeds C.
Input: n C, then a_1 .. a_n (1 <= n <= 10^5, 1 <= a_i, C <= 10^18).
Output: "g L" with L = -1 when the LCM is greater than C.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 0.4.5 and 0.4.6. The GCD of all numbers and their LCM, or -1 if the LCM exceeds C.
long long gcdLL(long long a, long long b) { return b == 0 ? a : gcdLL(b, a % b); }

pair<long long, long long> gcdAndLcm(const vector<long long>& a, long long C) {
    long long g = 0, L = 1;  // gcd(0, x) = x, lcm(1, x) = x
    bool tooBig = false;
    for (long long x : a) {
        g = gcdLL(g, x);
        if (tooBig) continue;
        long long q = L / gcdLL(L, x);  // lcm(L, x) = q * x
        if (q > C / x) tooBig = true;   // q * x > C, tested without computing q * x
        else L = q * x;
    }
    return {g, tooBig ? -1 : L};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long C;
    cin >> n >> C;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    pair<long long, long long> r = gcdAndLcm(a, C);
    cout << r.first << " " << r.second << "\n";
}
