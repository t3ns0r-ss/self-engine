/*
Problem: AtCoder ABC 282 C String Delimiter. Replace every ',' that is not between a pair of
'"' (the 1st and 2nd, the 3rd and 4th, ...) by '.'.
Input: N, then S (length N <= 2*10^5, an even number of '"').
Output: the new string.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    bool inside = false;  // the state: are we between an opening and a closing '"'?
    for (char& ch : s) {
        if (ch == '"') inside = !inside;
        else if (ch == ',' && !inside) ch = '.';
    }
    cout << s << "\n";
}
