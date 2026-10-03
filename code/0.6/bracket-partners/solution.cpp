/*
Problem: a string of the brackets ( ) [ ] { }. If it is properly nested, print for every position the
position of its partner (0-based); otherwise print NO.
Input: the string (length 1 .. 2*10^5).
Output: the partner positions separated by spaces, or NO.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> partner(n, -1);
    stack<int> open;  // positions of the opening brackets not matched yet; the top is the newest
    auto opener = [](char c) { return c == ')' ? '(' : c == ']' ? '[' : '{'; };
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            open.push(i);
        } else {
            if (open.empty() || s[open.top()] != opener(c)) {  // check before top() (Theorem 0.6.6)
                cout << "NO\n";
                return 0;
            }
            partner[i] = open.top();
            partner[open.top()] = i;
            open.pop();
        }
    }
    if (!open.empty()) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << partner[i] << (i + 1 < n ? ' ' : '\n');
}
