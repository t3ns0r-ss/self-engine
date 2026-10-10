#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3};
    int n = 3;
    // P1: the sum of a_i xor a_j over pairs. Brute: all pairs. Method: 2^b * c_b * (n - c_b) per bit.
    long long brute = 0, method = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute += a[i] ^ a[j];
    for (int b = 0; b < 3; b++) { long long c = 0; for (int x : a) c += x >> b & 1; method += (1LL << b) * c * (n - c); }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the sum of a_i and a_j over pairs. Method: 2^b * C(c_b, 2) per bit.
    brute = method = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute += a[i] & a[j];
    for (int b = 0; b < 3; b++) { long long c = 0; for (int x : a) c += x >> b & 1; method += (1LL << b) * c * (c - 1) / 2; }
    cout << "P2 brute=" << brute << " method=" << method << '\n';
    // N1: the sum of a_i + a_j over pairs (addition mixes bits), answered with the per-bit XOR formula.
    brute = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute += a[i] + a[j];
    method = 0;
    for (int b = 0; b < 3; b++) { long long c = 0; for (int x : a) c += x >> b & 1; method += (1LL << b) * c * (n - c); }
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: the largest a_i xor a_j for ONE pair, answered with the per-bit sum over all pairs.
    brute = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute = max(brute, (long long)(a[i] ^ a[j]));
    cout << "N2 brute=" << brute << " method=" << 6 << '\n';
}
