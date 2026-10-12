#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), bestStart = 0, bestLen = 0;
    for (int l = 0; l < n; l++)
        for (int r = l + 1; r <= n; r++) {
            string u = s.substr(l, r - l), v(u.rbegin(), u.rend());
            if (u == v && r - l > bestLen) bestStart = l, bestLen = r - l;
        }
    cout << s.substr(bestStart, bestLen) << "\n";
}
