#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> z(n, 0), pi(n, 0);
    for (int i = 1; i < n; i++) {
        int len = 0;
        while (i + len < n && s[len] == s[i + len]) len++;
        z[i] = len;
    }
    for (int i = 0; i < n; i++)
        for (int k = i; k >= 1; k--)
            if (s.compare(0, k, s, i + 1 - k, k) == 0) {
                pi[i] = k;
                break;
            }
    for (int i = 0; i < n; i++) cout << z[i] << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << pi[i] << (i + 1 < n ? ' ' : '\n');
}
