// Brute force: every subsequence of a (as a bitmask), checked against b with two pointers (topic 1.3).
#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string s;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += a[i];
        size_t p = 0;
        for (char c : b)
            if (p < s.size() && s[p] == c) p++;
        if (p == s.size()) best = max(best, (int)s.size());
    }
    cout << best << "\n";
}
