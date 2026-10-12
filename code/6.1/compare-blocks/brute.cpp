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
        int c = s.compare(a, len, s, b, len);
        cout << (c < 0 ? "<" : c == 0 ? "=" : ">") << "\n";
    }
}
