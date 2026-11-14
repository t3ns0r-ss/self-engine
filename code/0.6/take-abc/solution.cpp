/*
Problem: a string S of the letters A, B, C. While S contains ABC as a consecutive piece, remove the
leftmost ABC. Print the final string.
Input: S (1 <= |S| <= 2*10^5).
Output: the final string (an empty line if nothing is left).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Keep the letters in t and use t as a stack: push the next letter, then drop the newest ABC.
string takeAbc(const string& s) {
    string t;
    for (char c : s) {
        t += c;  // += does not copy the old text
        int m = t.size();
        if (m >= 3 && t.compare(m - 3, 3, "ABC") == 0) t.resize(m - 3);  // the last three letters were ABC
    }
    return t;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << takeAbc(s) << "\n";
}
