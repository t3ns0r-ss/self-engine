#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), best = 0;
    for (int l = 0; l < n; l++)
        for (int r = l + 1; r <= n; r++) {
            string u = s.substr(l, r - l), v(u.rbegin(), u.rend());
            if (u == v) best = max(best, r - l);
        }
    cout << best << "\n";
}
