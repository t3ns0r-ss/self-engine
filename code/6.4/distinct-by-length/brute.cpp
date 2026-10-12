#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    for (int len = 1; len <= n; len++) {
        set<string> all;
        for (int i = 0; i + len <= n; i++) all.insert(s.substr(i, len));
        cout << all.size() << (len < n ? " " : "\n");
    }
}
