/*
Problem: AtCoder ABC 282 C String Delimiter. Replace every ',' that is not between a pair of
'"' (the 1st and 2nd, the 3rd and 4th, ...) by '.'.
Input: N, then S (length N <= 2*10^5, an even number of '"').
Output: the new string.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Replace every ',' that is not between a pair of '"' by '.'. The state: inside a quoted part or not.
string replaceCommas(string s) {
    bool inside = false;
    for (char& ch : s) {
        if (ch == '"') inside = !inside;
        else if (ch == ',' && !inside) ch = '.';
    }
    return s;
}
// snippet:end

int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << replaceCommas(s) << "\n";
}
