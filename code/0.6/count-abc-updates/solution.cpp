/*
Problem: a string S of capital letters and Q queries "x c": set the x-th letter of S to c, then print how
many times ABC appears in S as a consecutive piece.
Input: N Q, then S, then Q lines "x c" (3 <= N <= 2*10^5, 1 <= Q <= 2*10^5, 1 <= x <= N).
Output: Q numbers, one per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Does ABC start at position i of s? (positions outside the string count as no)
bool abcAt(const string& s, int i) {
    return i >= 0 && i + 3 <= (int)s.size() && s.compare(i, 3, "ABC") == 0;
}

// Change s[x] to c (x is 0-based) and return how the number of ABC pieces changes.
// Only the three windows that contain position x can change, so this costs O(1), not O(n).
int setLetter(string& s, int x, char c) {
    int before = 0, after = 0;
    for (int i = x - 2; i <= x; i++) before += abcAt(s, i);
    s[x] = c;
    for (int i = x - 2; i <= x; i++) after += abcAt(s, i);
    return after - before;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    string s;
    cin >> n >> q >> s;
    int total = 0;
    for (int i = 0; i < n; i++) total += abcAt(s, i);
    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        total += setLetter(s, x - 1, c);
        cout << total << "\n";
    }
}
