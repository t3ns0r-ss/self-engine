// Removes "()" pairs until none is left; the depth is the number of rounds needed when every
// innermost pair is removed in each round.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int rounds = 0;
    while (!s.empty()) {
        string t;
        bool removed = false;
        for (size_t i = 0; i < s.size(); i++) {
            if (i + 1 < s.size() && s[i] == '(' && s[i + 1] == ')') {
                i++;
                removed = true;
            } else {
                t += s[i];
            }
        }
        if (!removed) break;
        s = t;
        rounds++;
    }
    if (s.empty()) cout << "YES " << rounds << "\n";
    else cout << "NO\n";
}
