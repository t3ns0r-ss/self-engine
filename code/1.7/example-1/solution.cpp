/*
Problem: ABC 171 E Red Scarf. N (even) cats wear integers x_1 .. x_N; a_i is the XOR of all x_j
except x_i. Given a_1 .. a_N, print x_1 .. x_N.
Input: N (2 <= N <= 2*10^5, N even), then a_1 .. a_N (0 <= a_i <= 10^9).
Output: x_1 .. x_N.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    int all = 0;  // XOR of every a_i, equal to the XOR of every x_j because n is even
    for (auto& v : a) {
        cin >> v;
        all ^= v;
    }
    for (int i = 0; i < n; i++) cout << (a[i] ^ all) << (i + 1 < n ? ' ' : '\n');  // x_i = a_i xor X
}
