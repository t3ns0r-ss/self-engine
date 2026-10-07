/*
Problem: the largest value of a_i AND a_j over all pairs i < j.
Input: n (2 <= n <= 2*10^5), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the largest AND.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int ans = 0;
    for (int b = 29; b >= 0; b--) {  // highest bit first (Theorem 1.7.4)
        int want = ans | (1 << b);
        int c = 0;  // values containing every bit of want
        for (int x : a)
            if ((x & want) == want) c++;
        if (c >= 2) ans = want;  // some pair keeps the decided bits and bit b
    }
    cout << ans << "\n";
}
