#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    long long total = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        int len = 0;
        while (i + len < n && s[len] == s[i + len]) len++;
        total += len;
    }
    cout << total << "\n";
}
