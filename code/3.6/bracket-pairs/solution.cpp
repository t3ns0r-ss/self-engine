/*
Problem: the length of the longest subsequence of a string of brackets ( ) [ ] that is a correct bracket sequence
(every bracket closed by the matching type, properly nested).
Input: a string s over the characters ( ) [ ] (1 <= |s| <= 500).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

bool matches(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']');
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // best[l][r] for the segment s[l..r]; an empty segment (l > r) counts 0
    vector<vector<int>> best(n + 1, vector<int>(n + 1, 0));
    auto get = [&](int l, int r) { return l > r ? 0 : best[l][r]; };
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            int value = get(l + 1, r);                    // s[l] is not used
            for (int k = l + 1; k <= r; k++)              // s[l] is matched with s[k] (Theorem 3.6.5)
                if (matches(s[l], s[k])) value = max(value, 2 + get(l + 1, k - 1) + get(k + 1, r));
            best[l][r] = value;
        }
    }
    cout << get(0, n - 1) << "\n";
}
