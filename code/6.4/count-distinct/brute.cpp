#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    set<string> all;
    for (int i = 0; i < n; i++)
        for (int len = 1; i + len <= n; len++) all.insert(s.substr(i, len));
    cout << all.size() << "\n";
}
