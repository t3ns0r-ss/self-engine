#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: triples (x, y, z) with 0 <= x, y, z <= 3 and x + 2y + 3z = 6. Brute: three loops. Method: two loops, x computed.
    int brute = 0, method = 0;
    for (int x = 0; x <= 3; x++) for (int y = 0; y <= 3; y++) for (int z = 0; z <= 3; z++) brute += x + 2 * y + 3 * z == 6;
    for (int y = 0; y <= 3; y++) for (int z = 0; z <= 3; z++) { int x = 6 - 2 * y - 3 * z; method += 0 <= x && x <= 3; }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the number of pairs (a, b) with 1 <= a, b <= 9. Brute: count them. Method: two nested loops.
    brute = 0, method = 0;
    for (int a = 1; a <= 9; a++) for (int b = 1; b <= 9; b++) brute++;
    method = 9 * 9;
    cout << "P2 brute=" << brute << " method=" << method << '\n';
    // N1: pairs i < j of 1 2 3 adding up to 4, with the inner loop starting at j = i instead of j = i + 1.
    vector<int> a = {1, 2, 3};
    brute = 0, method = 0;
    for (int i = 0; i < 3; i++) for (int j = i + 1; j < 3; j++) brute += a[i] + a[j] == 4;
    for (int i = 0; i < 3; i++) for (int j = i; j < 3; j++) method += a[i] + a[j] == 4;
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: pairs of 1 2 3 4 adding up to 5, with both i and j over every index.
    vector<int> b = {1, 2, 3, 4};
    brute = 0, method = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) brute += b[i] + b[j] == 5;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) method += i != j && b[i] + b[j] == 5;
    cout << "N2 brute=" << brute << " method=" << method << '\n';
}
