/*
Problem: print the sum of the XOR of every subarray of an array.
Input: n (1 <= n <= 10^5), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the sum over all pairs l <= r of a_l ^ ... ^ a_r (below 6 * 10^18).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.6. One pass over the array: for every prefix XOR value, add how many earlier prefix values differ from it at each bit.
long long sumOfSubarrayXors(const vector<int>& a) {
    long long total = 0;
    long long seen[30][2] = {};  // seen[b][v] = earlier prefix values whose bit b equals v
    int prefix = 0;
    for (int b = 0; b < 30; b++) seen[b][0] = 1;  // the empty prefix, value 0
    for (int x : a) {
        prefix ^= x;
        for (int b = 0; b < 30; b++) {
            int bit = (prefix >> b) & 1;
            total += (1LL << b) * seen[b][bit ^ 1];  // subarrays ending here whose XOR has bit b set
            seen[b][bit]++;
        }
    }
    return total;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << sumOfSubarrayXors(a) << "\n";
}
