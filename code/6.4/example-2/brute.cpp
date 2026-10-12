#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int k;
    cin >> s >> k;
    while (k--) {
        string p;
        cin >> p;
        cout << (s.find(p) != string::npos ? "YES" : "NO") << "\n";
    }
}
