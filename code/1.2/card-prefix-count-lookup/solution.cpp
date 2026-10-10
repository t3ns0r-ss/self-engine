#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: subarrays of 1 2 -1 2 with sum 3. Brute: all subarrays. Method: earlier prefix values P_j - 3.
    vector<int> a = {1, 2, -1, 2};
    int brute = 0, method = 0;
    for (int l = 0; l < 4; l++) for (int r = l, s = 0; r < 4; r++) { s += a[r]; brute += s == 3; }
    map<int, int> seen;
    seen[0] = 1;
    int P = 0;
    for (int x : a) { P += x; method += seen.count(P - 3) ? seen[P - 3] : 0; seen[P]++; }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: subarrays of 1 2 3 with sum divisible by 3. Method: equal remainders of prefix sums.
    vector<int> b = {1, 2, 3};
    brute = method = 0;
    for (int l = 0; l < 3; l++) for (int r = l, s = 0; r < 3; r++) { s += b[r]; brute += s % 3 == 0; }
    map<int, int> rem;
    rem[0] = 1;
    P = 0;
    for (int x : b) { P += x; method += rem[P % 3]; rem[P % 3]++; }
    cout << "P2 brute=" << brute << " method=" << method << '\n';
    // N1: subarrays of 1 2 with sum 3, with the prefix P_0 = 0 missing from the map.
    vector<int> c = {1, 2};
    brute = 0;
    for (int l = 0; l < 2; l++) for (int r = l, s = 0; r < 2; r++) { s += c[r]; brute += s == 3; }
    map<int, int> noZero;
    method = 0;
    P = 0;
    for (int x : c) { P += x; method += noZero.count(P - 3) ? noZero[P - 3] : 0; noZero[P]++; }
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: subarrays of -1 2 1 with even sum, with the raw remainder P % 2 (which can be negative).
    vector<int> d = {-1, 2, 1};
    brute = 0;
    for (int l = 0; l < 3; l++) for (int r = l, s = 0; r < 3; r++) { s += d[r]; brute += s % 2 == 0; }
    map<int, int> raw;
    raw[0] = 1;
    method = 0;
    P = 0;
    for (int x : d) { P += x; method += raw[P % 2]; raw[P % 2]++; }
    cout << "N2 brute=" << brute << " method=" << method << '\n';
}
