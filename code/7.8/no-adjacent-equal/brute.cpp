#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    do {
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++) ok = ok && s[i] != s[i - 1];
        if (ok) {
            cout << "YES\n";
            return 0;
        }
    } while (next_permutation(s.begin(), s.end()));
    cout << "NO\n";
}
