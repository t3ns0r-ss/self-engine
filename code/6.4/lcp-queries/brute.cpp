#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    while (q--) {
        int a, b;
        cin >> a >> b;
        int h = 0;
        while (a + h < n && b + h < n && s[a + h] == s[b + h]) h++;
        cout << h << "\n";
    }
}
