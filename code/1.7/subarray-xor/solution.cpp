/*
Problem: count the subarrays whose XOR is exactly k.
Input: n k (1 <= n <= 2*10^5, 0 <= k < 2^30), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the number of subarrays (up to n(n+1)/2, about 2*10^10).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    map<int, int> seen;  // prefix XOR value -> how many earlier prefixes have it
    seen[0] = 1;         // P_0 = 0
    int P = 0;
    long long count = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        P ^= a;
        auto it = seen.find(P ^ k);  // earlier P_i with P_i = P_j xor k (Theorem 1.7.2)
        if (it != seen.end()) count += it->second;
        seen[P]++;
    }
    cout << count << "\n";
}
