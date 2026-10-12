#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int q;
    cin >> s >> q;
    while (q--) {
        int a, b, len;
        cin >> a >> b >> len;
        a--, b--;
        cout << (s.compare(a, len, s, b, len) == 0 ? "YES" : "NO") << "\n";
    }
}
