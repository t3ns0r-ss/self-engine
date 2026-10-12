#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> sa(n);
    for (int& x : sa) cin >> x, x--;
    // The smallest string over the first n letters, in lexicographic order, whose suffix array is sa.
    string s(n, 'a');
    while (true) {
        vector<int> cur(n);
        iota(cur.begin(), cur.end(), 0);
        sort(cur.begin(), cur.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
        if (cur == sa) break;
        int i = n - 1;
        while (i >= 0 && s[i] == 'a' + n - 1) s[i] = 'a', i--;
        if (i < 0) { cout << -1 << "\n"; return 0; }
        s[i]++;
    }
    cout << s << "\n";
}
