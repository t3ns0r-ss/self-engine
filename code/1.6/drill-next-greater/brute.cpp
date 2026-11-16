#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; i++) {
        long long res = -1;
        for (int j = i + 1; j < n; j++) if (a[j] > a[i]) { res = a[j]; break; }
        cout << res << (i + 1 < n ? ' ' : '\n');
    }
}
