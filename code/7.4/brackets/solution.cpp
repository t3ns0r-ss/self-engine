#include <bits/stdc++.h>
using namespace std;

/*
Problem: a string of '(', ')' and '?' (up to 5·10^4 characters). Each '?' must become '(' at the cost a_i or ')' at the cost b_i.
Print the least total cost of making the string a correct bracket sequence, or -1 if that is impossible.
Input: the string, then for each '?' in order the two costs "a b".
Output: the least cost, or -1.
*/


// snippet:begin
// Theorem 7.4.2 (covering form): close every '?' at first; when the balance goes below zero, the '?' passed so far with the smallest
// extra cost (a - b) is opened instead, which repairs the balance by 2. The heap holds the extra costs of the '?' not yet opened.
long long cheapestBrackets(const string& s, const vector<pair<int, int>>& costs) {
    priority_queue<int, vector<int>, greater<int>> extra;
    long long total = 0;
    int balance = 0;
    size_t question = 0;
    for (char c : s) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        else {
            auto [open, close] = costs[question++];
            total += close, balance--, extra.push(open - close);
        }
        if (balance < 0) {
            if (extra.empty()) return -1;
            total += extra.top(), extra.pop(), balance += 2;
        }
    }
    return balance == 0 ? total : -1;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    vector<pair<int, int>> costs(count(s.begin(), s.end(), '?'));
    for (auto& [a, b] : costs) cin >> a >> b;
    cout << cheapestBrackets(s, costs) << "\n";
}
