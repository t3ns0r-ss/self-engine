#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    for (int mask = 0; mask < (1 << n); mask++) {  // bit i says whether item i takes a[i] (1) or b[i] (0)
        set<int> taken;
        for (int i = 0; i < n; i++) taken.insert(mask >> i & 1 ? a[i] : b[i]);
        if ((int)taken.size() == n) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}
