#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> borders, periods;
    for (int k = 1; k < n; k++)
        if (s.compare(0, k, s, n - k, k) == 0) borders.push_back(k);
    for (int p = 1; p <= n; p++) {
        bool ok = true;
        for (int i = 0; i + p < n; i++) ok = ok && s[i] == s[i + p];
        if (ok) periods.push_back(p);
    }
    for (const vector<int>& v : {borders, periods}) {
        cout << v.size();
        for (int x : v) cout << " " << x;
        cout << "\n";
    }
}
