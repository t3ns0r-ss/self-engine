/*
Problem: for n integers, count the subarrays whose sum equals K, and the subarrays whose sum is
divisible by m.
Input: n K m (1 <= n <= 2*10^5, |K| <= 10^15, 1 <= m <= 10^9), then a_1 .. a_n (|a_i| <= 10^9).
Output: "countEqualK countDivisibleByM".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.2. The number of subarrays with sum exactly K, and the number with sum divisible by m,
// from a map of how often each earlier prefix value occurred.
pair<long long, long long> countSubarrays(const vector<long long>& a, long long K, long long m) {
    map<long long, int> seen, seenMod;  // prefix sum (and its remainder) -> how many earlier prefixes had it
    long long P = 0, equalK = 0, divisible = 0;
    seen[0] = 1;  // P_0 = 0
    seenMod[0] = 1;
    for (long long x : a) {
        P += x;
        long long r = (P % m + m) % m;  // P can be negative
        auto it = seen.find(P - K);
        if (it != seen.end()) equalK += it->second;  // earlier P_i with P_i = P_j - K
        divisible += seenMod[r];                     // earlier P_i with the same remainder
        seen[P]++;
        seenMod[r]++;
    }
    return {equalK, divisible};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long K, m;
    cin >> n >> K >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    pair<long long, long long> r = countSubarrays(a, K, m);
    cout << r.first << " " << r.second << "\n";
}
