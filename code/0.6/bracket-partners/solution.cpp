/*
Problem: a string of the brackets ( ) [ ] { }. If it is properly nested, print for every position the
position of its partner (0-based); otherwise print NO.
Input: the string (length 1 .. 2*10^5).
Output: the partner positions separated by spaces, or NO.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.6. Partner positions of a properly nested bracket string, found with a stack of open positions.
// Returns false if the string is not properly nested.
bool bracketPartners(const string& s, vector<int>& partner) {
    int n = s.size();
    partner.assign(n, -1);
    stack<int> open;  // positions of the opening brackets not matched yet; the top is the newest
    auto opener = [](char c) { return c == ')' ? '(' : c == ']' ? '[' : '{'; };
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            open.push(i);
        } else {
            if (open.empty() || s[open.top()] != opener(c)) return false;  // check before top()
            partner[i] = open.top();
            partner[open.top()] = i;
            open.pop();
        }
    }
    return open.empty();
}
// snippet:end

int main() {
    string s;
    cin >> s;
    vector<int> partner;
    if (!bracketPartners(s, partner)) {
        cout << "NO\n";
        return 0;
    }
    int n = s.size();
    for (int i = 0; i < n; i++) cout << partner[i] << (i + 1 < n ? ' ' : '\n');
}
