#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    string s;
    cin >> n >> q >> s;
    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        s[x - 1] = c;
        int total = 0;
        for (int i = 0; i + 3 <= n; i++)
            if (s.substr(i, 3) == "ABC") total++;
        cout << total << "\n";
    }
}
