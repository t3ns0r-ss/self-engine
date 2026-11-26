/*
Problem: over all pairs i < j, print the sums of a_i XOR a_j, a_i AND a_j and a_i OR a_j.
Input: n (1 <= n <= 10^5), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the three sums on one line (each below 6*10^18).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.5. The sums of a_i xor a_j, a_i and a_j, a_i or a_j over all pairs i < j, from the number c of values with each bit.
array<long long, 3> pairSums(const vector<int>& a) {
    long long n = a.size(), sx = 0, sa = 0, so = 0, pairs = n * (n - 1) / 2;
    for (int b = 0; b < 30; b++) {
        long long c = 0;  // how many values have bit b
        for (int x : a) c += (x >> b) & 1;
        long long w = 1LL << b;
        sx += w * (c * (n - c));                       // exactly one has the bit
        sa += w * (c * (c - 1) / 2);                   // both have it
        so += w * (pairs - (n - c) * (n - c - 1) / 2); // not "neither"
    }
    return {sx, sa, so};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    array<long long, 3> r = pairSums(a);
    cout << r[0] << " " << r[1] << " " << r[2] << "\n";
}
