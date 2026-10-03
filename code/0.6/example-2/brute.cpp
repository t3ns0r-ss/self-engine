// Inserts into a vector exactly as described, finding i - 1 by a scan: O(N^2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> a = {0};
    for (int i = 1; i <= n; i++) {
        int pos = find(a.begin(), a.end(), i - 1) - a.begin();
        if (s[i - 1] == 'L') a.insert(a.begin() + pos, i);
        else a.insert(a.begin() + pos + 1, i);
    }
    for (int k = 0; k <= n; k++) cout << a[k] << (k < n ? ' ' : '\n');
}
