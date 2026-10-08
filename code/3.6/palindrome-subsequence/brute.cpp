// Brute force: every subsequence as a bitmask, checked for being a palindrome.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        string t;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) t += s[i];
        if (equal(t.begin(), t.end(), t.rbegin())) best = max(best, (int)t.size());
    }
    cout << best << "\n";
}
