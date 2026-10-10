/*
Problem: the largest value of a_i AND a_j over all pairs i < j.
Input: n (2 <= n <= 2*10^5), then a_1 .. a_n (0 <= a_i < 2^30).
Output: the largest AND.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.4. The largest a_i & a_j over pairs i < j: decide the bits from the top; keep a bit when two values
// contain every decided bit and this one.
int maxAndPair(const vector<int>& a) {
    int ans = 0;
    for (int b = 29; b >= 0; b--) {
        int want = ans | (1 << b);
        int c = 0;  // values containing every bit of want
        for (int x : a)
            if ((x & want) == want) c++;
        if (c >= 2) ans = want;
    }
    return ans;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << maxAndPair(a) << "\n";
}
