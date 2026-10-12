#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, flags;
    int k;
    cin >> s >> flags >> k;
    int n = s.size();
    set<string> seen;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            int badCount = 0;
            for (int i = l; i <= r; i++) badCount += flags[s[i] - 'a'] - '0';
            if (badCount <= k) seen.insert(s.substr(l, r - l + 1));
        }
    cout << seen.size() << "\n";
}
