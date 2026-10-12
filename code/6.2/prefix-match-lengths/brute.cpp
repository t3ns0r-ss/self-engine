#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    for (size_t i = 0; i < s.size(); i++) {
        size_t len = 0;
        while (i + len < s.size() && len < t.size() && s[i + len] == t[len]) len++;
        cout << len << (i + 1 < s.size() ? ' ' : '\n');
    }
}
