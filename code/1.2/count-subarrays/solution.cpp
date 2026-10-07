/*
Problem: for n integers, count the subarrays whose sum equals K, and the subarrays whose sum is
divisible by m.
Input: n K m (1 <= n <= 2*10^5, |K| <= 10^15, 1 <= m <= 10^9), then a_1 .. a_n (|a_i| <= 10^9).
Output: "countEqualK countDivisibleByM".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long K, m;
    cin >> n >> K >> m;
    map<long long, int> seen;     // prefix sum -> how many earlier prefixes had it
    map<long long, int> seenMod;  // prefix sum mod m -> how many earlier prefixes had it
    long long P = 0, equalK = 0, divisible = 0;  // counts reach n(n+1)/2, about 2*10^10
    seen[0] = 1;                                   // P_0 = 0 (Theorem 1.2.2, condition 2)
    seenMod[0] = 1;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        P += a;
        long long r = (P % m + m) % m;  // P can be negative (condition 3)
        auto it = seen.find(P - K);
        if (it != seen.end()) equalK += it->second;  // earlier P_i with P_i = P_j - K
        divisible += seenMod[r];                     // earlier P_i with the same remainder
        seen[P]++;
        seenMod[r]++;
    }
    cout << equalK << " " << divisible << "\n";
}
