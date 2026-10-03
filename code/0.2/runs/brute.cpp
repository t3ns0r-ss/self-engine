// Checks every substring directly.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), blocks = 0, longest = 0;
    long long single = 0;
    for (int i = 0; i < n; i++)
        if (i == 0 || s[i] != s[i - 1]) blocks++;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            bool same = true;
            for (int k = l; k <= r; k++) same = same && s[k] == s[l];
            if (same) {
                single++;
                longest = max(longest, r - l + 1);
            }
        }
    cout << blocks << " " << longest << " " << single << "\n";
}
