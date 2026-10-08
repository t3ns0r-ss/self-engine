// Brute force: every bitmask subset, sorted, collected in a set (which removes repeats and sorts).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    set<vector<int>> all;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> s;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s.push_back(a[i]);
        sort(s.begin(), s.end());
        all.insert(s);
    }
    cout << all.size() << "\n";
    for (auto& s : all) {
        cout << s.size();
        for (int x : s) cout << " " << x;
        cout << "\n";
    }
}
