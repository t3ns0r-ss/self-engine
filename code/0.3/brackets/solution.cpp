/*
Problem: is a string of '(' and ')' a valid bracket sequence? If so, also print its nesting depth.
Input: the string (length 1..10^6).
Output: "YES d" with the maximum depth d, or "NO".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.3. One pass with the state "opens minus closes so far": the maximum depth if the string
// is a valid bracket sequence, otherwise -1.
int bracketDepth(const string& s) {
    int depth = 0, best = 0;
    bool ok = true;
    for (char ch : s) {
        depth += (ch == '(') ? 1 : -1;
        if (depth < 0) ok = false;  // a ')' with nothing open: no later character can fix it
        best = max(best, depth);
    }
    return (ok && depth == 0) ? best : -1;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    int d = bracketDepth(s);
    if (d >= 0) cout << "YES " << d << "\n";
    else cout << "NO\n";
}
