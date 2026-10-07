// Scans every queried substring for "AC".
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    string s;
    cin >> n >> q >> s;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int c = 0;
        for (int i = l - 1; i + 1 <= r - 1; i++) c += s[i] == 'A' && s[i + 1] == 'C';
        cout << c << "\n";
    }
}
