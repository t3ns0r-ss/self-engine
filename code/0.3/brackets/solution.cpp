/*
Problem: is a string of '(' and ')' a valid bracket sequence? If so, also print its nesting depth.
Input: the string (length 1..10^6).
Output: "YES d" with the maximum depth d, or "NO".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int depth = 0, best = 0;  // the state: opens minus closes in the prefix read so far
    bool ok = true;
    for (char ch : s) {
        depth += (ch == '(') ? 1 : -1;
        if (depth < 0) ok = false;  // a ')' with nothing open: no later character can fix it
        best = max(best, depth);
    }
    if (ok && depth == 0) cout << "YES " << best << "\n";
    else cout << "NO\n";
}
