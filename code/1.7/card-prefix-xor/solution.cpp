#include <bits/stdc++.h>
using namespace std;

long long countXor(const vector<int>& a, int k, bool withZero) {
    map<int, int> seen;
    if (withZero) seen[0] = 1;
    long long count = 0;
    int P = 0;
    for (int x : a) {
        P ^= x;
        auto it = seen.find(P ^ k);
        if (it != seen.end()) count += it->second;
        seen[P]++;
    }
    return count;
}

int main() {
    vector<int> a = {1, 2, 3, 4};
    // P1: the XOR of a[2..3] (1-based). Brute: XOR the elements. Method: P_3 xor P_1.
    vector<int> P = {0};
    for (int x : a) P.push_back(P.back() ^ x);
    cout << "P1 brute=" << (a[1] ^ a[2]) << " method=" << (P[3] ^ P[1]) << '\n';
    // P2: the subarrays of 1 2 3 4 with XOR 3. Brute: all subarrays. Method: the prefix map.
    int brute = 0;
    for (int l = 0; l < 4; l++) for (int r = l, x = 0; r < 4; r++) { x ^= a[r]; brute += x == 3; }
    cout << "P2 brute=" << brute << " method=" << countXor(a, 3, true) << '\n';
    // N1: the subarrays with XOR at most 1, counted as the subarrays with XOR exactly 1.
    brute = 0;
    for (int l = 0; l < 4; l++) for (int r = l, x = 0; r < 4; r++) { x ^= a[r]; brute += x <= 1; }
    cout << "N1 brute=" << brute << " method=" << countXor(a, 1, true) << '\n';
    // N2: the subarrays with XOR exactly 1, with P_0 = 0 missing from the map.
    brute = 0;
    for (int l = 0; l < 4; l++) for (int r = l, x = 0; r < 4; r++) { x ^= a[r]; brute += x == 1; }
    cout << "N2 brute=" << brute << " method=" << countXor(a, 1, false) << '\n';
}
