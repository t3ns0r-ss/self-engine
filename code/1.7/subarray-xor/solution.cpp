/*
Problem: count the subarrays whose XOR is exactly k.
Input: n k (1 <= n <= 2*10^5, 0 <= k < 2^30), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the number of subarrays (up to n(n+1)/2, about 2*10^10).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.2. The number of subarrays with XOR exactly k: pairs of prefix values with P_i = P_j xor k.
long long countXorSubarrays(const vector<int>& a, int k) {
    map<int, int> seen;  // prefix XOR value -> how many earlier prefixes have it
    seen[0] = 1;         // P_0 = 0
    int P = 0;
    long long count = 0;
    for (int x : a) {
        P ^= x;
        auto it = seen.find(P ^ k);  // earlier P_i with P_i = P_j xor k
        if (it != seen.end()) count += it->second;
        seen[P]++;
    }
    return count;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << countXorSubarrays(a, k) << "\n";
}
