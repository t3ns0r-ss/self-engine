/*
Problem: ABC 171 E Red Scarf. N (even) cats wear integers x_1 .. x_N; a_i is the XOR of all x_j
except x_i. Given a_1 .. a_N, print x_1 .. x_N.
Input: N (2 <= N <= 2*10^5, N even), then a_1 .. a_N (0 <= a_i <= 10^9).
Output: x_1 .. x_N.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Given a_i = (XOR of all x_j except x_i) with n even, recover x: the XOR of all a_i equals the XOR of all x_j,
// so x_i = a_i xor that total.
vector<int> recoverHats(const vector<int>& a) {
    int all = 0;
    for (int v : a) all ^= v;
    vector<int> x(a.size());
    for (int i = 0; i < (int)a.size(); i++) x[i] = a[i] ^ all;
    return x;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    vector<int> x = recoverHats(a);
    for (int i = 0; i < n; i++) cout << x[i] << (i + 1 < n ? ' ' : '\n');
}
