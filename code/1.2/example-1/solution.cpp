/*
Problem: ABC 122 C GeT AC. A string S of length N over A, C, G, T and Q queries "l r" (1-based):
how many times does "AC" occur inside S[l..r]?
Input: N Q (2 <= N <= 10^5, 1 <= Q <= 10^5), S, then Q lines "l r" (l < r).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    string s;
    cin >> n >> q >> s;
    // starts[k] = number of positions i < k (0-based) where "AC" starts, i.e. s[i] = 'A', s[i+1] = 'C'
    vector<int> starts(n + 1, 0);
    for (int i = 0; i < n; i++) starts[i + 1] = starts[i] + (i + 1 < n && s[i] == 'A' && s[i + 1] == 'C');
    while (q--) {
        int l, r;
        cin >> l >> r;
        // an occurrence inside S[l..r] starts at a 1-based position from l to r - 1,
        // which is 0-based l - 1 .. r - 2
        cout << starts[r - 1] - starts[l - 1] << "\n";
    }
}
