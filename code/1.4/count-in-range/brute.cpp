// Scans the whole array for every query.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    while (q--) {
        long long L, R;
        cin >> L >> R;
        int c = 0;
        for (long long x : a) c += L <= x && x <= R;
        cout << c << "\n";
    }
}
