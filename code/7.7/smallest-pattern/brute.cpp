#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 1);
    do {
        bool ok = true;
        for (int i = 0; i < n; i++) ok = ok && ((s[i] == 'I') == (p[i] < p[i + 1]));
        if (ok) break;
    } while (next_permutation(p.begin(), p.end()));
    for (int i = 0; i <= n; i++) cout << p[i] << (i < n ? " " : "\n");
}
