#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1732 Finding Borders. A border of a string is a prefix that is also a suffix but not the whole string.
Print all border lengths of the given string (length up to 10^6) in increasing order.
Input: the string. Output: the border lengths in increasing order (an empty line if there are none).
*/

vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// snippet:begin
// The border lengths in increasing order, from the Z-function: the suffix s[i..] is a prefix exactly when z[i] = n - i,
// and then n - i is a border length. Going from the right end to the left gives increasing lengths. Uses zFunction.
vector<int> borders(const string& s) {
    int n = s.size();
    vector<int> z = zFunction(s), result;
    for (int i = n - 1; i >= 1; i--)
        if (z[i] == n - i) result.push_back(n - i);
    return result;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    vector<int> b = borders(s);
    for (size_t i = 0; i < b.size(); i++) cout << b[i] << (i + 1 < b.size() ? ' ' : '\n');
    if (b.empty()) cout << "\n";
}
