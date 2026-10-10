/*
Problem: ABC 122 C GeT AC. A string S of length N over A, C, G, T and Q queries "l r" (1-based):
how many times does "AC" occur inside S[l..r]?
Input: N Q (2 <= N <= 10^5, 1 <= Q <= 10^5), S, then Q lines "l r" (l < r).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// starts[k] = number of positions i < k where "AC" starts (s[i] = 'A', s[i+1] = 'C'): a prefix sum of a 0/1 array.
vector<int> acStarts(const string& s) {
    int n = s.size();
    vector<int> starts(n + 1, 0);
    for (int i = 0; i < n; i++) starts[i + 1] = starts[i] + (i + 1 < n && s[i] == 'A' && s[i + 1] == 'C');
    return starts;
}
// An occurrence inside S[l..r] (1-based) starts at a position from l to r - 1: starts[r - 1] - starts[l - 1].
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    string s;
    cin >> n >> q >> s;
    vector<int> starts = acStarts(s);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << starts[r - 1] - starts[l - 1] << "\n";
    }
}
