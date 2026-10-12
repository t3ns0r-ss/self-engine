#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string t;
    cin >> n >> t;
    long long total = 1, count = 0;
    for (int i = 0; i < n; i++) total *= 26;
    for (long long code = 0; code < total; code++) {
        string s(n, 'a');
        long long x = code;
        for (int i = 0; i < n; i++, x /= 26) s[i] = 'a' + x % 26;
        if (s.find(t) != string::npos) count++;
    }
    cout << count % 1000000007 << "\n";
}
