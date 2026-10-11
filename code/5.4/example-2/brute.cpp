#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cin >> q;
    while (q--) {
        int p, k;
        cin >> p >> k;
        int steps = 0;
        for (p--; p < n; p += a[p] + k) steps++;
        cout << steps << "\n";
    }
}
