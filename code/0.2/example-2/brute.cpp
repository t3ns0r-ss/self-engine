// Puts every one-character-repeated substring into a set of strings and prints its size.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    set<string> seen;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n && s[r] == s[l]; r++) seen.insert(s.substr(l, r - l + 1));
    cout << seen.size() << "\n";
}
